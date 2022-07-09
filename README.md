# Installing
1. Firstly, install `rocksdb` library
2. Secondly, install `nlohmann_json` library
3. Thirdly, build with cmake program in `rocksdb_uvm_support`:
  1. `cd rocksdb_uvm_support`
  2. `mkdir build`
  3. `cd build`
  4. `cmake ..`
  5. `make`
4. After building, need to run it:  `./rocksdb_uvm_support`. It will create column families which UVM needed
5. After column families were created - need to build `UVM`. 

# ToDo:
- [ ] BIP32 & BIP44
- [ ] Pseudonymous
- [ ] VM
- [ ] ZK-STARK
- [ ] DECENTRALIZATION
- [ ] GPU counting Proof of Knowledge

# Tests

```markdown
Recent tests show that current blockhain is able to operate on ***ten thousand*** transaction easily.
***UVM*** proccess with 10.000 transactions consumed:
- 22 Megabytes memory usage
- 13 threads
The block with 10,000 transactions was counted in 40 minutes with one stream on the Apple M1.
```

# Dependencies

- rocksdb
- nlohmann_json
- boost

# VM Opcodes

|hex num|name   		|note   													|
|	:---|	:---:		|				:---:										|
|000	|stop   		|stop execution of the contract 							|
|001	|loop   		|-   														|
|002	|swap   		|swaps two references   									|
|003	|inc 			|increase value 											|
|004	|sub 			|substract value 											|
|005	|divide 		|devide value 												|
|006	|mul 			|multiply value 											|
|007	|i_div 			|a % b														|
|008	|i_xor 			|a ^ b														|
|009	|inv 			|!a															|
|010	|l_shift		|a << val													|
|011	|r_shift		|a >> val													|
|012	|pop 			|pop value													|
|013	|push 			|push value													|
|014	|dup 			|duplicate(memcpy)											|
|015	|i_or 			|a |
|016	|i_and 			|a & b			 											|
|017	|i_return		|return;													|
|018	|i_sha3 		|sha3_256		 											|
|019	|i_balance 		|get balance of address										|
|020	|i_timestamp	|get timestamps												|
|021	|i_blockhash	|get blockhash												|
|022	|i_chainid 		|returns chain_id											|
|023	|i_memory_store	|store value in memory		 								|
|024	|i_memory_value|return;													|
|025	|i_storage_store|stores key : value		 									|
|026	|create 		|create contract 											|
|027	|destruct 		|destruct contract and returns all holdings to their holders|
|028	|jump 			|jumps to instruction <num> in stack						|
|029	|equal |a  == b	|
|030	|gt |a > b	|
|031	|lt |a < b	|
|032	|egt |a >= b	|
|033	|elt |a <=b	|
|034	|address |address of current contract	|
|035	|invalid |invalid	|

# Vm Data Structures

| num  | name       | sizeof                             | note                          |
| ---- | ---------- | ---------------------------------- | ----------------------------- |
| 1    | i32        | 40 bytes                           |                               |
| 2    | u64        | 8 bytes                            |                               |
| 3    | u128       | 80 bytes                           |                               |
| 4    | u256       | 80 bytes                           |                               |
| 5    | d64        | 40 bytes                           | number of decimal places is 4 |
| 6    | boolean    | 40 bytes                           |                               |
| 7    | collection | sum of sizes all structures inside |                               |
| 8    | string     | 1 byte * length (ASCII)            |                               |
| 9    | Object     | 32 bytes                           |                               |

# VM Technical Structures
|Num   |name   		|note   												     |
|	:---		|	:---:		 |				:---:											|
|0			   	 |instruction_stack   		|Stack with all instructions of the program 				  |
|1	|program_counter |it contains an address of currently executed instruction. Program will be executed by moving PC through instruction set, reading opcodes and executing them |
|2	|stack_pointer |it contains information about number of elements stored on the stack. It always points on the top of it |
|3	|frame_pointer |frame pointer (for local scope) |
|4	|Constant-pool 1 |used for String, int, float, ~~Class(maybe in the future)~~ and stores reference to each string |
|5	|Constant-pool 2 |used for double, long, or a dynamically-computed constant and stores reference to each |

> Note:
>
> For pools implementation can be used

```c++
std::reference_wrapper<int>
  // or
std::ref()  
  // need more time to read and choose
```



# Update for structures and instructions

#### 04.07.22

>Each instruction means starts with types name:
>
>- i[^1] - integer
>- u64 - uint64_t
>- u128 - uint128_t
>- u256 - uint256_t
>- b - bool
>- c - collection
>- d - double
>- st - string 
> 

[^1]: for uint32_t incompatible
## Updated Opcode list (not finished)

| num  | name        | note                                  |
| ---- | ----------- | ------------------------------------- |
| 000  | stop        | -                                     |
| 001  | loop        | -                                     |
| 002  | iconst_0    | push int value 0 onto the stack       |
| 003  | iconst_1    | push int value 1 onto the stack       |
| 004  | iconst_2    | push int value 2 onto the stack       |
| 005  | iconst_3    | push int value 3 onto the stack       |
| 006  | iconst_4    | push int value 4 onto the stack       |
| 007  | u64const_0  | push uint64_t value 0 onto the stack  |
| 008  | u64const_1  | push uint64_t value 1 onto the stack  |
| 009  | u64const_2  | push uint64_t value 2 onto the stack  |
| 010  | u64const_3  | push uint64_t value 3 onto the stack  |
| 011  | u64const_4  | push uint64_t value 4 onto the stack  |
| 012  | u128const_0 | push uint128_t value 0 onto the stack |
| 013  | u128const_1 | push uint128_t value 1 onto the stack |
| 014  | u128const_2 | push uint128_t value 2 onto the stack |
| 015  | u128const_3 | push uint128_t value 3 onto the stack |
| 016  | u128const_4 | push uint128_t value 4 onto the stack |
| 017  | u256const_0 | push uint256_t value 0 onto the stack |
| 018  | u256const_1 | push uint256_t value 1 onto the stack |
| 019  | u256const_2 | push uint256_t value 2 onto the stack |
| 020  | u256const_3 | push uint256_t value 3 onto the stack |
| 021  | u256const_4 | push uint256_t value 4 onto the stack |
|      |             |                                       |
|      |             |                                       |
|      |             |                                       |
|      |             |                                       |
|      |             |                                       |
|      |             |                                       |
|      |             |                                       |
|      |             |                                       |
|      |             |                                       |
|      |             |                                       |
|      |             |                                       |
|      |             |                                       |
|      |             |                                       |
|      |             |                                       |
|      |             |                                       |
|      |             |                                       |
|      |             |                                       |
