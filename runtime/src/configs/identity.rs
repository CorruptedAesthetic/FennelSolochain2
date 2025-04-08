use crate::{Runtime, RuntimeEvent};
use frame_support::parameter_types;

parameter_types! {
    pub const IdentityMaxSize: u32 = 1024;
}

impl pallet_identity::Config for Runtime {
    type RuntimeEvent = RuntimeEvent;
    type WeightInfo = pallet_identity::weights::SubstrateWeight<Runtime>;
    type MaxSize = IdentityMaxSize;
}
