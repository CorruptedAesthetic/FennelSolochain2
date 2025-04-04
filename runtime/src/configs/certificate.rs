use crate::{
    AccountId, Balance, Balances, Runtime, RuntimeEvent,
};
use frame_support::{parameter_types, traits::LockIdentifier};

parameter_types! {
    pub const CertificateLockIdentifier: LockIdentifier = *b"fnlcertf";
    pub const CertificateLockPrice: u32 = 100;
}

impl pallet_certificate::Config for Runtime {
    type RuntimeEvent = RuntimeEvent;
    type WeightInfo = pallet_certificate::weights::SubstrateWeight<Runtime>;
    type Currency = Balances;
    type LockId = CertificateLockIdentifier;
    type LockPrice = CertificateLockPrice;
}
