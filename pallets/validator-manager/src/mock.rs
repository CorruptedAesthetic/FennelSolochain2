#![cfg(test)]

use crate as pallet_validator_manager;
use frame_support::{
    parameter_types,
    traits::{ConstU16, ConstU64, GenesisBuild},
};
use sp_core::H256;
use sp_runtime::{
    testing::UintAuthorityId,
    traits::{BlakeTwo256, IdentityLookup},
    BuildStorage,
};
use frame_system as system;

type Block = frame_system::mocking::MockBlock<Test>;
type AccountId = u64;

frame_support::construct_runtime!(
    pub enum Test
    {
        System: frame_system,
        Session: pallet_session,
        ValidatorManager: pallet_validator_manager,
    }
);

impl system::Config for Test {
    type BaseCallFilter = frame_support::traits::Everything;
    type BlockWeights = ();
    type BlockLength = ();
    type DbWeight = ();
    type RuntimeOrigin = RuntimeOrigin;
    type RuntimeCall = RuntimeCall;
    type Nonce = u64;
    type Hash = H256;
    type Hashing = BlakeTwo256;
    type AccountId = AccountId;
    type Lookup = IdentityLookup<Self::AccountId>;
    type Block = Block;
    type RuntimeEvent = RuntimeEvent;
    type BlockHashCount = ConstU64<250>;
    type Version = ();
    type PalletInfo = PalletInfo;
    type AccountData = ();
    type OnNewAccount = ();
    type OnKilledAccount = ();
    type SystemWeightInfo = ();
    type SS58Prefix = ConstU16<42>;
    type OnSetCode = ();
    type MaxConsumers = frame_support::traits::ConstU32<16>;
}

parameter_types! {
    pub const DisabledValidatorsThreshold: Perbill = Perbill::from_percent(33);
}

impl pallet_session::Config for Test {
    type RuntimeEvent = RuntimeEvent;
    type ValidatorId = AccountId;
    type ValidatorIdOf = pallet_validator_manager::ValidatorOf<Test>;
    type ShouldEndSession = pallet_session::PeriodicSessions<ConstU64<1>, ConstU64<0>>;
    type NextSessionRotation = pallet_session::PeriodicSessions<ConstU64<1>, ConstU64<0>>;
    type SessionManager = ValidatorManager;
    type SessionHandler = TestSessionHandler;
    type Keys = UintAuthorityId;
    type WeightInfo = ();
}

impl pallet_validator_manager::Config for Test {
    type RuntimeEvent = RuntimeEvent;
    type PrivilegedOrigin = frame_system::EnsureRoot<AccountId>;
}

pub struct TestSessionHandler;
impl pallet_session::SessionHandler<AccountId> for TestSessionHandler {
    const KEY_TYPE_IDS: &'static [sp_runtime::KeyTypeId] = &[];
    fn on_genesis_session<T: pallet_session::OpaqueKeys>(_validators: &[(AccountId, T)]) {}
    fn on_new_session<T: pallet_session::OpaqueKeys>(
        _changed: bool,
        _validators: &[(AccountId, T)],
        _queued_validators: &[(AccountId, T)],
    ) {
    }
    fn on_disabled(_validator_index: u32) {}
}

// Build genesis storage according to the mock runtime.
pub fn new_test_ext() -> sp_io::TestExternalities {
    let mut t = system::GenesisConfig::<Test>::default().build_storage().unwrap();
    
    pallet_session::GenesisConfig::<Test> {
        keys: vec![
            (1, UintAuthorityId(1)),
            (2, UintAuthorityId(2)),
            (3, UintAuthorityId(3)),
        ],
    }
    .assimilate_storage(&mut t)
    .unwrap();

    t.into()
} 