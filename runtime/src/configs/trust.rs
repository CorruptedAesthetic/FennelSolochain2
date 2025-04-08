use crate::{Runtime, RuntimeEvent};
use frame_support::parameter_types;

parameter_types! {
    pub const TrustParameterMaxSize: u32 = 1024;
}

impl pallet_trust::Config for Runtime {
    type RuntimeEvent = RuntimeEvent;
    type WeightInfo = pallet_trust::weights::SubstrateWeight<Runtime>;
    type MaxTrustParameterSize = TrustParameterMaxSize;
}
