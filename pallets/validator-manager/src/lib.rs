#![cfg_attr(not(feature = "std"), no_std)]

//! A pallet for managing validators on Fennel Solonet.

extern crate alloc;
use alloc::vec::Vec;
use sp_staking::SessionIndex;
use sp_std::marker::PhantomData;
use sp_runtime::traits::Convert;
use frame_support::traits::Get;

pub use pallet::*;

type Session<T> = pallet_session::Pallet<T>;

/// A type used to convert an account ID into a validator ID.
pub struct ValidatorOf<T>(PhantomData<T>);

impl<T: Config> Convert<T::AccountId, Option<T::AccountId>> for ValidatorOf<T> {
    fn convert(account: T::AccountId) -> Option<T::AccountId> {
        Some(account)
    }
}

#[frame_support::pallet]
pub mod pallet {
    use super::*;
    use frame_support::{dispatch::DispatchResult, pallet_prelude::*, traits::EnsureOrigin};
    use frame_system::pallet_prelude::*;

    #[pallet::pallet]
    #[pallet::without_storage_info]
    pub struct Pallet<T>(_);

    /// Configuration for the validator manager.
    #[pallet::config]
    pub trait Config: frame_system::Config + pallet_session::Config {
        /// The overreaching event type.
        type RuntimeEvent: From<Event<Self>> + IsType<<Self as frame_system::Config>::RuntimeEvent>;

        /// Privileged origin that can add or remove validators.
        type PrivilegedOrigin: EnsureOrigin<<Self as frame_system::Config>::RuntimeOrigin>;

        /// Minimum number of validators that should be maintained
        #[pallet::constant]
        type MinAuthorities: Get<u32>;
    }

    #[pallet::event]
    #[pallet::generate_deposit(pub(super) fn deposit_event)]
    pub enum Event<T: Config> {
        /// New validators were added to the set.
        ValidatorsRegistered(Vec<T::ValidatorId>),
        /// Validators were removed from the set.
        ValidatorsDeregistered(Vec<T::ValidatorId>),
    }

    /// Validators that should be retired.
    #[pallet::storage]
    pub(crate) type ValidatorsToRetire<T: Config> =
        StorageValue<_, Vec<T::ValidatorId>, ValueQuery>;

    /// Validators that should be added.
    #[pallet::storage]
    pub(crate) type ValidatorsToAdd<T: Config> = StorageValue<_, Vec<T::ValidatorId>, ValueQuery>;

    #[pallet::call]
    impl<T: Config> Pallet<T> {
        /// Add new validators to the set.
        ///
        /// The new validators will be active from current session + 2.
        #[pallet::call_index(0)]
        #[pallet::weight({100_000})]
        pub fn register_validators(
            origin: OriginFor<T>,
            validators: Vec<T::ValidatorId>,
        ) -> DispatchResult {
            T::PrivilegedOrigin::ensure_origin(origin)?;

            validators.clone().into_iter().for_each(|v| ValidatorsToAdd::<T>::append(v));

            Self::deposit_event(Event::ValidatorsRegistered(validators));
            Ok(())
        }

        /// Remove validators from the set.
        ///
        /// The removed validators will be deactivated from current session + 2.
        #[pallet::call_index(1)]
        #[pallet::weight({100_000})]
        pub fn deregister_validators(
            origin: OriginFor<T>,
            validators: Vec<T::ValidatorId>,
        ) -> DispatchResult {
            T::PrivilegedOrigin::ensure_origin(origin)?;

            validators.clone().into_iter().for_each(|v| ValidatorsToRetire::<T>::append(v));

            Self::deposit_event(Event::ValidatorsDeregistered(validators));
            Ok(())
        }
    }
}

impl<T: Config> pallet_session::SessionManager<T::ValidatorId> for Pallet<T> {
    fn new_session(new_index: SessionIndex) -> Option<Vec<T::ValidatorId>> {
        let mut validators = Session::<T>::validators();

        // Apply pending changes
        ValidatorsToRetire::<T>::take().iter().for_each(|v| {
            if let Some(pos) = validators.iter().position(|r| r == v) {
                validators.swap_remove(pos);
            }
        });

        ValidatorsToAdd::<T>::take().into_iter().for_each(|v| {
            if !validators.contains(&v) {
                validators.push(v);
            }
        });

        // Check if we have enough validators
        let min_validators = T::MinAuthorities::get() as usize;
        
        if validators.len() < min_validators {
            // Not enough validators, let the chain use its default set
            None
        } else {
            // We have enough validators
            Some(validators)
        }
    }

    fn end_session(_: SessionIndex) {}

    fn start_session(_start_index: SessionIndex) {}
}

impl<T: Config> pallet_session::historical::SessionManager<T::ValidatorId, ()> for Pallet<T> {
    fn new_session(new_index: SessionIndex) -> Option<Vec<(T::ValidatorId, ())>> {
        <Self as pallet_session::SessionManager<_>>::new_session(new_index)
            .map(|r| r.into_iter().map(|v| (v, Default::default())).collect())
    }

    fn start_session(start_index: SessionIndex) {
        <Self as pallet_session::SessionManager<_>>::start_session(start_index)
    }

    fn end_session(end_index: SessionIndex) {
        <Self as pallet_session::SessionManager<_>>::end_session(end_index)
    }
} 