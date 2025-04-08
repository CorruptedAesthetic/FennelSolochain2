use crate::{Balances, Runtime, RuntimeEvent};
use frame_support::{parameter_types, traits::LockIdentifier};

parameter_types! {
    pub const SignalMaxSize: u32 = 1024;
    pub const SignalLockIdentifier: LockIdentifier = *b"fnlsignl";
    pub const SignalLockPrice: u32 = 100;
}

impl pallet_signal::Config for Runtime {
    type RuntimeEvent = RuntimeEvent;
    type Currency = Balances;
    type WeightInfo = pallet_signal::weights::SubstrateWeight<Runtime>;
    type MaxSize = SignalMaxSize;
    type LockId = SignalLockIdentifier;
    type LockPrice = SignalLockPrice;
}
