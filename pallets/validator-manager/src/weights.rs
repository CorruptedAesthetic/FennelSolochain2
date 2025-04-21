#![cfg_attr(rustfmt, rustfmt_skip)]
#![allow(unused_parens)]
#![allow(unused_imports)]

use frame_support::{traits::Get, weights::{Weight, constants::RocksDbWeight}};
use sp_std::marker::PhantomData;

/// Weight functions for pallet_validator_manager
pub trait WeightInfo {
    fn register_validators(v: u32) -> Weight;
    fn deregister_validators(v: u32) -> Weight;
}

/// Weights for pallet_validator_manager using the Substrate node and recommended hardware.
pub struct SubstrateWeight<T>(PhantomData<T>);
impl<T: frame_system::Config> WeightInfo for SubstrateWeight<T> {
    // Storage: ValidatorManager ValidatorsToAdd (r:1 w:1)
    // Storage: Session Validators (r:0 w:0)
    fn register_validators(v: u32, ) -> Weight {
        Weight::from_parts(21_000_000, 0)
            // Standard Error: 0
            .saturating_add(Weight::from_parts(25_000, 0).saturating_mul(v as u64))
            .saturating_add(T::DbWeight::get().reads(1))
            .saturating_add(T::DbWeight::get().writes(1))
    }
    // Storage: ValidatorManager ValidatorsToRetire (r:1 w:1)
    // Storage: Session Validators (r:0 w:0)
    fn deregister_validators(v: u32, ) -> Weight {
        Weight::from_parts(21_000_000, 0)
            // Standard Error: 0
            .saturating_add(Weight::from_parts(25_000, 0).saturating_mul(v as u64))
            .saturating_add(T::DbWeight::get().reads(1))
            .saturating_add(T::DbWeight::get().writes(1))
    }
} 