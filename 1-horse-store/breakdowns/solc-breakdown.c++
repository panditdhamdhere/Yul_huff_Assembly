// 0x6080604052348015600e575f80fd5b5060a580601a5f395ff3fe6080604052348015600e575f80fd5b50600436106030575f3560e01c8063cdfead2e146034578063e026c017146045575b5f80fd5b6043603f3660046059565b5f55565b005b5f5460405190815260200160405180910390f35b5f602082840312156068575f80fd5b503591905056fea26469706673582212207910617a71b4be7f09d5233a9d39e01604428c424be7d25a89f5544ffcff977a64736f6c63430008190033

// 3 Sections
// Section 1: Contract Creation
// Section 2: Runtime
// Section 3: Metadata



// Contract creation code
// free memory pointer
PUSH1 0x80     // [0x80] -> on to the stack
PUSH1 0x40     // [0x80, 0x40] -> on to the stack
MSTORE

// Whats this chunck do
// If some1 sent value with this call, jump to the 0x0E pc/jumpdest 
CALLVALUE     // [msg.value]
DUP1          // [msg.value, msg.value]
ISZERO        // [msg.value ==0 , msg.value]
PUSH1 0x0e    /// [0x0E, msg.value ==0 , msg.value]
JUMPI         // [msg.value]
PUSH0         // [0x00, msg.value]
DUP1          // [0x00, 0x00, msg.value]
REVERT        // [msg.value]

// jump dest if msg.value == 0
// sticks the runtime code on chain
JUMPDEST       // [msg.value]
POP            // []
PUSH1 0xa5     // [0xa5]
DUP1           // [0xa5, 0xa5]
PUSH1 0x1a     // [0x001b, 0xa5, 0xa5]
PUSH0          // [0x00, 0x001b, 0xa5, 0xa5]
CODECOPY       // [0xa5] memory:[runtime code]
PUSH0         // [0x00, 0xa5]
RETURN           //[]
INVALID         // []

// 2. Runtime code
// entry point of all calls
PUSH1 0x80        // free memory pointer
PUSH1 0x40
MSTORE


// checking for msg.value, and if given reverting 
CALLVALUE        // [msg.value]
DUP1             // [msg.value, msg.value]
ISZERO           // [msg.value ==0 , msg.value]
PUSH1 0x0e       // [0x0e, msg.value ==0 , msg.value]
JUMPI            // [msg.value] 

// jump to "continue" if msg.value == 0
PUSH0            // [0x00, msg.value]
DUP1             // [0x00, 0x00, msg.value]
REVERT           // [msg.value]


// if msg.value ==0 , start here!
JUMPDEST          //[msg.value]
POP                // []
PUSH1 0x04        // [0x04]
CALLDATASIZE       // [calldata_size, 0x04]
LT                // [calldata_size < 0x04]  
PUSH1 0x30        // [0x30, calldata_size < 0x04]
JUMPI              // []


// function dispatching in solidty for readnumberofhorses
PUSH0            // []
CALLDATALOAD     //[32 bytes of calldata] 
PUSH1 0xe0        // [0xe0, 32 bytes of calldata]
SHR               //[calldata [0:4]]  function selector

// dispatching for set number of horses
DUP1             // [func_selector, func_selector]
PUSH4 0xcdfead2e   // [0xcdfead2e, func_selector, func_selector]
EQ               //[func_selector == 0xcdfead2e, func_selector]
PUSH1 0x34       // [0x34, func_selector == 0xcdfead2e, func_selector]
JUMPI        // [func_selector]

// if func_selector == 0xcdfead2e -> set_number_of_horses

DUP1               // [func_selector, func_selector] 
PUSH4 0xe026c017    // [0xe026c017, func_selector, func_selector]
EQ             // [func_selector == 0xe026c017, func_selector]
PUSH1 0x45         // [0x45, func_selector == 0xe026c017, func_selector]
JUMPI       // [func_selector]
// if func_selector == 0xe026c017 -> get_number_of_horses

// calldata_jump
// revert jumpdest
JUMPDEST    // []
PUSH0   // [0]
DUP1      // [0, 0]
REVERT     // []

//update HorseNumberDest 1
JUMPDEST      // [func_selector]
PUSH1 0x43     // [0x43, func_selector]
PUSH1 0x3f    // [0x3f, 0x43, func_selector]
CALLDATASIZE    // [calldata_size, 0x3f, 0x43, func_selector]
PUSH1 0x04     // [0x04, calldata_size, 0x3f, 0x43, func_selector]
PUSH1 0x59  // [0x59, 0x04, calldata_size, 0x3f, 0x43, func_selector]
JUMP       //[0x04, calldata_size, 0x3f, 0x43, func_selector]

// jump dest 4
// we can finally run an sstore to save our value to storage:
// function dispatch
// checked for msg.value
// checked that calldata is long enough
// received the number to use from the calldata
JUMPDEST  // [calldata_size, calldata(of numberToUpdate), 0x43, func_selector]
PUSH0  //[0, calldata_size, calldata(of numberToUpdate), ,0x43, func_selector]
SSTORE //[ 0x43, func_selector]
JUMP    // [ func_selector]

// jump dest 5

JUMPDEST  // [ func_selector]
STOP     // [ func_selector]
JUMPDEST
PUSH0
SLOAD
PUSH1 0x40
MLOAD
SWAP1
DUP2
MSTORE
PUSH1 0x20
ADD
PUSH1 0x40
MLOAD
DUP1
SWAP2
SUB
SWAP1
RETURN

// update horse number jump dest 2
JUMPDEST                 // [0x04, calldata_size, 0x3f, 0x43, func_selector]
PUSH0                    // [0, 0x04, calldata_size, 0x3f, 0x43, func_selector]
PUSH1 0x20              // [0x20, 0, 0x04, calldata_size, 0x3f, 0x43, func_selector]
DUP3                    // [0x04, 0x20, 0, 0x04, calldata_size, 0x3f, 0x43, func_selector]
DUP5                    // [calldata_size, 0x04, 0x20, 0, 0x04, calldata_size, 0x3f, 0x43, func_selector]
SUB                    //[calldata_size - 0x04, 0x20, 0, 0x04, calldata_size, 0x3f, 0x43, func_selector]
SLT      // [calldata_size - 0x04 < 0x20,  0, 0x04,  calldata_size, 0x3f, 0x43, func_selector]
ISZERO           // [more_calldata_than_selector, calldata_size - 0x04 < 0x20 == true,  0, 0x04,  calldata_size, 0x3f, 0x43, func_selector]
PUSH1 0x68    // [0x68, more_calldata_than_selector, calldata_size - 0x04 < 0x20 == true,  0, 0x04,  calldata_size, 0x3f, 0x43, func_selector]
JUMPI // [ 0, 0x04,  calldata_size, 0x3f, 0x43, func_selector]

// revert if there is not enough calldata
PUSH0  // [ 0, 0, 0x04,  calldata_size, 0x3f, 0x43, func_selector]
DUP1  // [0, 0, 0, 0x04,  calldata_size, 0x3f, 0x43, func_selector]
REVERT  // [  0, 0x04,  calldata_size, 0x3f, 0x43, func_selector]

//updateHorseNumber jump dest 3
JUMPDEST  //[0, 0x04,  calldata_size, 0x3f, 0x43, func_selector]
POP      // [0x04,  calldata_size, 0x3f, 0x43, func_selector]
CALLDATALOAD   // [calldata(of numberToUpdate), 0x04,  calldata_size, 0x3f, 0x43, func_selector]
SWAP2  // [calldata_size, 0x04,  calldata(of numberToUpdate), 0x3f, 0x43, func_selector]
SWAP1  // [0x04, calldata_size, calldata(of numberToUpdate), 0x3f, 0x43, func_selector]
POP  // [calldata_size, calldata(of numberToUpdate), 0x3f, 0x43, func_selector]
JUMP
INVALID
LOG2
PUSH5 0x6970667358
INVALID
SLT
KECCAK256
PUSH26 0x10617a71b4be7f09d5233a9d39e01604428c424be7d25a89f554
INVALID
INVALID
SELFDESTRUCT
SWAP8
PUSH27 0x64736f6c63430008190033