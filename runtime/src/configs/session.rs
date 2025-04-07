use crate::{Runtime, RuntimeEvent, Aura, Grandpa, MINUTES, opaque};
use frame_support::{parameter_types, traits::ConstU32};

parameter_types! {
    pub const Period: u32 = 15 * MINUTES;
    pub const Offset: u32 = 0;
}

impl pallet_session::Config for Runtime {
    type RuntimeEvent = RuntimeEvent;
    type ValidatorId = <Self as frame_system::Config>::AccountId;
    type ValidatorIdOf = opaque::ValidatorIdOf;
    type ShouldEndSession = pallet_session::PeriodicSessions<Period, Offset>;
    type NextSessionRotation = pallet_session::PeriodicSessions<Period, Offset>;
    type SessionManager = ();  // We can use () for a basic setup
    type SessionHandler = (Aura, Grandpa);
    type Keys = opaque::SessionKeys;
    type WeightInfo = pallet_session::weights::SubstrateWeight<Runtime>;
}
