use crate::{Runtime, RuntimeEvent};
use frame_support::parameter_types;

parameter_types! {
    pub const KeystoreMaxSize: u32 = 1024;
}

impl pallet_keystore::Config for Runtime {
    type RuntimeEvent = RuntimeEvent;
    type WeightInfo = pallet_keystore::weights::SubstrateWeight<Runtime>;
    type MaxSize = KeystoreMaxSize;
}
