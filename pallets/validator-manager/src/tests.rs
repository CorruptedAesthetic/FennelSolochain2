#![cfg(test)]

use crate::{mock::*, Error};
use frame_support::assert_ok;

#[test]
fn register_validators_works() {
    new_test_ext().execute_with(|| {
        // Ensure we start with the expected validators from genesis
        let validators = Session::validators();
        assert_eq!(validators, vec![1, 2, 3]);

        // Register new validators
        assert_ok!(ValidatorManager::register_validators(RuntimeOrigin::root(), vec![4, 5]));
        
        // Change session to trigger validator update
        Session::rotate_session();
        Session::rotate_session();
        
        // Check that the new validators were added
        let validators = Session::validators();
        assert_eq!(validators, vec![1, 2, 3, 4, 5]);
    });
}

#[test]
fn deregister_validators_works() {
    new_test_ext().execute_with(|| {
        // Ensure we start with the expected validators from genesis
        let validators = Session::validators();
        assert_eq!(validators, vec![1, 2, 3]);

        // Deregister validators
        assert_ok!(ValidatorManager::deregister_validators(RuntimeOrigin::root(), vec![1, 2]));
        
        // Change session to trigger validator update
        Session::rotate_session();
        Session::rotate_session();
        
        // Check that the validators were removed
        let validators = Session::validators();
        assert_eq!(validators, vec![3]);
    });
}

#[test]
fn both_register_and_deregister_works() {
    new_test_ext().execute_with(|| {
        // Register a new validator and deregister an existing one
        assert_ok!(ValidatorManager::register_validators(RuntimeOrigin::root(), vec![4]));
        assert_ok!(ValidatorManager::deregister_validators(RuntimeOrigin::root(), vec![1]));
        
        // Change session to trigger validator update
        Session::rotate_session();
        Session::rotate_session();
        
        // Check that the changes were applied correctly
        let validators = Session::validators();
        assert_eq!(validators, vec![2, 3, 4]);
    });
} 