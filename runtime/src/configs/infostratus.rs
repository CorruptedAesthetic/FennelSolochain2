use crate::{Balances, Runtime, RuntimeEvent};
use frame_support::{parameter_types, traits::LockIdentifier};

parameter_types! {
    pub const InfostratusMaxSize: u32 = 1024;
    pub const InfostratusLockIdentifier: LockIdentifier = *b"infstrts";
    pub const InfostratusLockPrice: u32 = 100;
}

impl pallet_infostratus::Config for Runtime {
    type RuntimeEvent = RuntimeEvent;
    type WeightInfo = pallet_infostratus::weights::SubstrateWeight<Runtime>;
    type Currency = Balances;
    type MaxSize = InfostratusMaxSize;
    type LockId = InfostratusLockIdentifier;
    type LockPrice = InfostratusLockPrice;
}

