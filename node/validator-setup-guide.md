# Validator Setup Guide for Fennel Solonet

This guide outlines the process for setting up and managing validators on the Fennel Solonet chain using the validator-manager pallet.

## Prerequisites

- Fennel Solonet node binary
- Two or more machines (or one machine running multiple nodes)
- Access to polkadot.js Apps UI

## 1. Starting the First Validator Node (Alice)

Start the first validator node (Alice) with these parameters:

```bash
cd ~/fennel_project/fennel-solonet
cargo run --release -- --alice --chain=local --base-path ~/tmp/a --port=30334 --rpc-port 9944 --rpc-cors=all --rpc-methods=Unsafe --rpc-external
```

After Alice's node starts, look for the node identity in the logs:

```
Local node identity is: 12D3KooWXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
```

Note this ID as you'll need it for connecting other nodes.

## 2. Starting the Second Validator Node (Bob)

Start Bob's node with similar parameters, but include Alice's node ID as a bootnode:

```bash
cd ~/fennel_project/fennel-solonet
cargo run --release -- --bob --chain=local --base-path ~/tmp/b --port=30335 --rpc-port 9945 --rpc-cors=all --rpc-methods=Unsafe --rpc-external --bootnodes /ip4/127.0.0.1/tcp/30334/p2p/ALICE_NODE_ID
```

Replace `ALICE_NODE_ID` with the actual node ID from Alice's logs.

## 3. Generating Session Keys

Session keys are required for validators to participate in consensus. Generate these for each node:

1. Connect to Alice's node in polkadot.js Apps (http://localhost:9944)
2. Go to "Developer" → "RPC calls"
3. Select "author" → "rotateKeys"
4. Execute the call and save the hex string result
5. Repeat for Bob's node by connecting to http://localhost:9945

## 4. Setting Session Keys

Session keys must be set for each validator account:

1. Connect to Alice's node in polkadot.js
2. Go to "Developer" → "Extrinsics"
3. Select "session" → "setKeys"
4. Select Alice's account in the sender dropdown
5. Split her rotated key in half (64 characters each half)
6. Enter the first half for Aura and the second half for Grandpa
7. Use "0x" for the proof parameter
8. Submit the transaction
9. Repeat for Bob's account by selecting Bob in the sender dropdown and using his keys

If Bob doesn't have funds for the transaction:
1. Go to "Developer" → "Sudo" → "sudo" → "sudoAs"
2. For "who", enter Bob's address
3. For "call", select "session" → "setKeys"
4. Enter Bob's split keys
5. Submit with Alice as sudo

## 5. Registering Validators

Use the validator-manager pallet to register validators:

1. Connect to Alice's node in polkadot.js
2. Go to "Developer" → "Sudo"
3. Select "validatorManager" → "registerValidators"
4. Enter the validator addresses:
   - Alice: 5GrwvaEF5zXb26Fz9rcQpDWS57CtERHpNehXCPcNoHGKutQY
   - Bob: 5FHneW46xGXgs5mUiveU4sbTyGBzmstUspZC92UhjJM694ty
5. Submit with Alice as sudo

## 6. Waiting for Activation

After registration, validators aren't immediately active:

1. Check if validators are in the queue:
   - "Chain State" → "validatorManager" → "validatorsToAdd()"
2. Monitor session rotations:
   - "Chain State" → "session" → "currentIndex()"
3. After two session rotations, check:
   - "Chain State" → "session" → "validators()" - should include registered validators
4. Check node logs for block production messages:
   ```
   🙌 Starting consensus session...
   🎁 Prepared block for proposing...
   ```

## 7. Removing Validators

To remove a validator:

1. Go to "Developer" → "Sudo"
2. Select "validatorManager" → "removeValidator"
3. Enter the validator's address to remove
4. Submit with Alice as sudo
5. Check the removal queue:
   - "Chain State" → "validatorManager" → "validatorsToRemove()"
6. After two session rotations, the validator should be removed from:
   - "Chain State" → "session" → "validators()"
7. The removed validator's node will return to "Idle" state

## Troubleshooting

- **Session Keys Issues**: Ensure session keys are properly generated and set for each validator
- **Node Connection Issues**: Verify bootnode parameters and network connectivity
- **Validator Not Activated**: Check session keys are set correctly and wait for multiple session rotations
- **Node Idle State**: If a node remains idle despite being registered, try removing and re-adding the validator with fresh session keys

## Common Addresses

- Alice: 5GrwvaEF5zXb26Fz9rcQpDWS57CtERHpNehXCPcNoHGKutQY
- Bob: 5FHneW46xGXgs5mUiveU4sbTyGBzmstUspZC92UhjJM694ty 


A few important points:
Any node can serve as a bootnode - there's nothing special about Alice in this regard
Once nodes are connected to the network, they'll discover other peers automatically
Existing connections between nodes will remain even if the original bootnode goes offline
Having multiple validators helps with network resilience - if Alice goes offline but Bob is still running, the network will continue to produce blocks
For better fault tolerance in a production environment, you might want to set up dedicated bootnodes that aren't validators but just serve as network entry points. But for a test network, using validators as bootnodes works fine.