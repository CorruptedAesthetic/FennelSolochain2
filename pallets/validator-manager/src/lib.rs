#![cfg_attr(not(feature = "std"), no_std)]

//! A pallet for managing validators on Fennel Solonet.

extern crate alloc;
use alloc::vec::Vec;
use sp_staking::SessionIndex;
use sp_std::marker::PhantomData;
use sp_runtime::traits::Convert;
use frame_support::traits::Get;

pub use pallet::*;

// Add mocks and tests modules
#[cfg(test)]
pub mod mock;

#[cfg(test)]
pub mod tests;

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
        ValidatorsRegistered { validators: Vec<T::ValidatorId> },
        /// A validator was removed from the set.
        ValidatorRemoved { validator: T::ValidatorId },
    }

    #[pallet::error]
    pub enum Error<T> {
        /// The validator is already in the set.
        ValidatorAlreadyAdded,
        /// The account is not a validator.
        NotValidator,
    }

    /// Validators that should be removed.
    #[pallet::storage]
    #[pallet::getter(fn validators_to_remove)]
    pub(crate) type ValidatorsToRemove<T: Config> =
        StorageValue<_, Vec<T::ValidatorId>, ValueQuery>;

    /// Validators that should be added.
    #[pallet::storage]
    #[pallet::getter(fn validators_to_add)]
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

            let mut current_validators_to_add = ValidatorsToAdd::<T>::get();
            
            for validator in validators.clone() {
                // Check if the validator is already in the to_add list
                ensure!(!current_validators_to_add.contains(&validator), Error::<T>::ValidatorAlreadyAdded);
                
                // Add to the queue
                current_validators_to_add.push(validator);
            }
            
            ValidatorsToAdd::<T>::put(current_validators_to_add);

            Self::deposit_event(Event::ValidatorsRegistered { validators });
            Ok(())
        }

        /// Remove a validator from the set.
        ///
        /// The removed validator will be deactivated from current session + 2.
        #[pallet::call_index(1)]
        #[pallet::weight({100_000})]
        pub fn remove_validator(
            origin: OriginFor<T>,
            validator: T::ValidatorId,
        ) -> DispatchResult {
            T::PrivilegedOrigin::ensure_origin(origin)?;
            
            // Check if this is a known validator
            let validators = Session::<T>::validators();
            ensure!(validators.contains(&validator), Error::<T>::NotValidator);

            // Add to removal queue
            let mut validators_to_remove = ValidatorsToRemove::<T>::get();
            validators_to_remove.push(validator.clone());
            ValidatorsToRemove::<T>::put(validators_to_remove);

            Self::deposit_event(Event::ValidatorRemoved { validator });
            Ok(())
        }
    }
}

impl<T: Config> pallet_session::SessionManager<T::ValidatorId> for Pallet<T> {
    fn new_session(_new_index: SessionIndex) -> Option<Vec<T::ValidatorId>> {
        let mut validators = Session::<T>::validators();

        // Apply pending changes
        let validators_to_remove = ValidatorsToRemove::<T>::take();
        validators_to_remove.iter().for_each(|v| {
            if let Some(pos) = validators.iter().position(|r| r == v) {
                validators.swap_remove(pos);
            }
        });

        let validators_to_add = ValidatorsToAdd::<T>::take();
        validators_to_add.into_iter().for_each(|v| {
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

#[cfg(test)]
impl<T: Config> Pallet<T> {
    pub fn new_session(new_index: SessionIndex) -> Option<Vec<T::ValidatorId>> {
        <Self as pallet_session::SessionManager<_>>::new_session(new_index)
    }
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