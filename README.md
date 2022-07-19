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
Recent tests show that current blockhain is able to operate on ten thousand transaction easily.
UVM proccess with 10.000 transactions consumed:
- 22 Megabytes memory usage
The block with 10,000 transactions was counted in 40 minutes with one thread on the Apple M1.
```

# Dependencies

- rocksdb
- nlohmann_json
- boost

# VM Opcodes

|hex num|name   		|args |note   													|examples |Stack [before]→[after] |exception |Implemented(true/false) |
|	:---|	:---:		|	----|				:---:										|	----|	----|	----|	----|
|000	|stop   		| - |stop execution of the contract 							| stop |[no change] | - |false |
| 001     | go_to            | int             | goes to another instruction at *branchoffset*                | go_to 2          |[no change] | - |true |
|002	|swap_references   		| int,int         |swaps two references. indexing starts from top of stack   									| swap 1 3 |value1,value2→value2,value1 | - |true |
|003	|iadd 			| num, num |adding value 											| |value1,value2→result | - |true |
|004	|isub 			| num, num |subtract value 											| |value1,value2→result | - |true |
|005	|idivide 		| num, num |devide value 												| |value1,value2→result | - |true |
|006	|imul 			| num, num |multiply value 											| |value1,value2→result | - |true |
|007	|imod 			| int, int |a % b														| |value1,value2→result |- |true |
|008	|ixor 			| int, int |a ^ b														| |value1,value2→result |- |true |
|009	|inv 			| num |!a															| |value→!value | - |true |
|010	|ilshift		| int, int |a << val													| |value1,value2→result |second parameter  < int32 max value |true |
|011	|irshift		| int |a >> val													| |value1,value2→result |- |true |
|012	|pop 			| Object |pop value													| |value→ | - | |
|013	|push 			| Object |push value													| |→value | - | |
|014	|dup 			| Object |duplicate from top of the stack											| |value→value1,value1 | - | |
|015	|ior 			| num |a \|\| b | |value1,value2→result | - | |
|016	|iand 			| int |a & b			 											| |value1,value2→result |- | |
|017	|return		| - |return;													| |[no change] | - | |
|018	|osha3 		| Object |sha3_256 value on top of the stack.		 											| |value→sha3(value) | - | |
|019	|balance 		| string |get balance of address										| |→value | - | |
|020	|timestamp	| - |get timestamps												| |→value | - | |
|021	|blockhash	| - |get blockhash												| |→value | - | |
|022	|chainid 		| - |returns chain_id											| |→value | - | |
| 023     | create           | -               | create contract                                              |                  | [no change]                          | - | |
| 024     | destruct         | string          | destruct contract and returns all holdings to their holders  |                  | [no change]                          | - | |
| 025     | address          | -               | address of current contract                                  |                  |→value | - | |
| 026     | invalid          | -               | invalid                                                      |                  |                                      | - | |
| 027     | iconst_0         | int             | push int value 0 onto the stack.                             | i_const          | → 0                                  | - | |
| 028     | iconst_1         | int             | push int value 1 onto the stack                              |                  | → 1                                  | - | |
| 029     | iconst_2         | int             | push int value 2 onto the stack                              |                  | → 2                                  | - | |
| 030     | iconst_3         | int             | push int value 3 onto the stack                              |                  | → 3                                  | - | |
| 031     | iconst_4         | int             | push int value 4 onto the stack                              |                  | → 4                                  | - | |
| 032     | u64const_0       | -               | push uint64_t value 0 onto the stack                         |                  | → 0                                  | - | |
| 033     | u64const_1       | -               | push uint64_t value 1 onto the stack                         |                  | → 1                                  | - | |
| 034     | u64const_2       | -               | push uint64_t value 2 onto the stack                         |                  | → 2                                  | - | |
| 035     | u64const_3       | -               | push uint64_t value 3 onto the stack                         |                  | → 3                                  | - | |
| 036     | u64const_4       | -               | push uint64_t value 4 onto the stack                         |                  | → 4                                  | - | |
| 037     | u128const_0      | -               | push uint128_t value 0 onto the stack                        |                  | → 0                                  | - | |
| 038     | u128const_1      | -               | push uint128_t value 1 onto the stack                        |                  | → 1                                  | - | |
| 039     | u128const_2      | -               | push uint128_t value 2 onto the stack                        |                  | → 2                                  | - | |
| 040     | u128const_3      | -               | push uint128_t value 3 onto the stack                        |                  | → 3                                  | - | |
| 041     | u128const_4      | -               | push uint128_t value 4 onto the stack                        |                  | → 4                                  | - | |
| 042     | u256const_0      | -               | push uint256_t value 0 onto the stack.                       |                  | → 0                                  | - | |
| 043     | u256const_1      | -               | push uint256_t value 1 onto the stack                        |                  | → 1                                  | - | |
| 044     | u256const_2      | -               | push uint256_t value 2 onto the stack                        |                  | → 2                                  | - | |
| 045     | u256const_3      | -               | push uint256_t value 3 onto the stack                        |                  | → 3                                  | - | |
| 046     | u256const_4      | -               | push uint256_t value 4 onto the stack                        |                  | → 4                                  | - | |
| 047     | ostore_0         | int             | push object value into local 0                               |                  | [no change]                          | - |true |
| 048     | ostore_1         | int             | push object value into local 1                               |                  | [no change]                          | - |true |
| 049     | ostore_2         | int             | push object value into local 2                               |                  | [no change]                          | - |true |
| 050     | ostore_3         | int             | push object value into local 3                               |                  | [no change]                          | - |true |
| 051     | ldc              | int index       | load #index from blockhain data.                                                                                                                              If program looks like: [60, 1], it'll load first value from blockchain data[^1] onto the stack.                                                                                                                 If program looks like: [60, 2], it'll load second value from blockchain data[^1]onto the stack. |                  | → value                              | - |true |
| 052     | oload_0          | int index       | load value from local_#index onto top of stack               | iload 1          | → value                              | - |true |
| 053     | oload_1          | int index       | load value from local_#index onto top of stack               | iload 1          | → value                              | - |true |
| 054     | oload_2          | int index       | load value from local_#index onto top of stack               | iload 1          | → value                              | - |true |
| 055     | oload_3          | int index       | load value from local_#index onto top of stack               | iload 1          | → value                              | - |true |
| 056     | swap             | -               | swaps two top elements                                       | swap             | value1,value2→value2,value1          | - |true |
| 057     | if_acmpeq        | Object ,Object  | checks if two values (Object or string) on top of the stack are equal. next index - index of next instruction. (a == b) | if_acmpeq 23     | [no change]                          | - | |
| 058     | if_acmpne        | Object , Object | checks if two values (Object or string) on top of the stack are not equal. next index - index of next instruction. (a != b) | if_acmpne 23     | [no change]                          | - | |
| 059     | if_icmpeq        | Object, Object  | checks if two integers (int32, uint64, uint128, uint256) on top of the stack are equal. next index - index of next instruction. (a == b) | if_icmpeq 23     | [no change]                          | - | |
| 060     | if_icmpge        | num,num         | checks if two integers (int32, uint64, uint128, uint256) on top of the stack are greater than or equal. next index - index of next instruction. (a >= b) | if_icmpge 23     | [no change]                          | - | |
| 061     | if_icmpgt        | num,num         | checks if two integers (int32, uint64, uint128, uint256) on top of the stack are greater than. next index - index of next instruction. (a > b) | if_icmpgt 23     | [no change]                          | - | |
| 062     | if_icmple        | num,num         | checks if two integers (int32, uint64, uint128, uint256) on top of the stack are less than or equal. next index - index of next instruction. (a <= b) | if_icmple 23     | [no change]                          | - | |
| 063     | if_icmplt        | num,num         | checks if two integers (int32, uint64, uint128, uint256) on top of the stack are less. next index - index of next instruction. (a < b) | if_icmplt 23     | [no change]                          | - | |
| 064     | if_icmpne        | num,num         | checks if two integers (int32, uint64, uint128, uint256) on top of the stack are not equal. next index - index of next instruction. (a != b) | if_icmpne 23     | [no change]                          | - | |
| 065     | ifeq             | num             | checks if integer (int32, uint64, uint128, uint256) on top of the stack are 0. next index - index of next instruction. (a == 0) | ifeq 23          | [no change]                          | - | |
| 066     | ifge             | num             | checks if integer (int32, uint64, uint128, uint256) on top of the stack greater than or equal to 0. next index - index of next instruction. (a >= 0) | ifge 23          | [no change]                          | - | |
| 067     | ifgt             | num             | checks if integer (int32, uint64, uint128, uint256) on top of the stack greater than 0. next index - index of next instruction. (a > 0) | ifgt 23          | [no change]                          | - | |
| 068     | ifle             | num             | checks if integer (int32, uint64, uint128, uint256) on top of the stack less than or equal to 0. next index - index of next instruction. (a <= 0) | ifle 23          | [no change]                          | - | |
| 069     | iflt             | num             | checks if integer (int32, uint64, uint128, uint256) on top of the stack less than 0. next index - index of next instruction. (a < 0) | iflt 23          | [no change]                          | - | |
| 070     | ifne             | num             | checks if integer (int32, uint64, uint128, uint256) on top of the stack not equals 0. next index - index of next instruction. (a != 0) | ifne 23          | [no change]                          | - | |
| 071     | ifnonnull        | Object          | checks if value (Object or string) on top of the stack are not null. next index - index of next instruction. (a != null) | ifnonnull 23     | [no change]                          | - | |
| 072     | ifnull           | Object          | checks if value (Object or string) on top of the stack are not null. next index - index of next instruction. (a == null) | ifnull 23        | [no change]                          | - | |
| 073     | nop              | -               | perform no operation                                         | nop              | [no change]                          | - | |
| 074     | collectionlength | collection      | push array length on top of the stack by getting length of collection which is on top of the stack | collectionlength | collection→collection,length(uint64) | - | |
| 075     | dconst_0         | -               | push int value 0.0 onto the stack.                           | dconst_0         | → 0.0                                | - | |
| 076     | dconst_1         | -               | push int value 1.0 onto the stack.                           | dconst_1         | → 1.0                                | - | |
| 077     | u64add           | num, num        | adding value                                                 |                  | value1,value2→value1+value2          | - |true |
| 078     | u128add          | num, num        | adding value                                                 |                  | value1,value2→value1+value2          | - |true |
| 079     | u256add          | num, num        | adding value                                                 |                  | value1,value2→value1+value2          | - |true |
| 080     | dadd             | num, num        | adding value                                                 |                  | value1,value2→value1+value2          | - |true |
| 081     | u64sub           | num, num        | substract value                                              |                  | value1,value2→value1-value2          | - |true |
| 082     | u128sub          | num, num        | substract value                                              |                  | value1,value2→value1-value2          | - |true |
| 083     | u256sub          | num, num        | substract value                                              |                  | value1,value2→value1-value2          | - |true |
| 084     | dsub             | num, num        | substract value                                              |                  |value1,value2→value1-value2 | - |true |
| 085 | u64divide | num, num | devide value | |value1,value2→value1/value2 | - |true |
| 086 | u64mul | num, num | multiply value | |value1,value2→value1*value2 | - |true |
| 087 | u64mod | int, int | a % b | |value1,value2→value1%value2 |double |true |
| 088 | u64xor | int, int | a ^ b | |value1,value2→value1^value2 |double |true |
| 089 | u64inv | num | !a | |value→!value | - |true |
| 090 | u64lshift | int, int | a << val | |value1,value2→value1<<value2 |second parameter  < int32 max value |true |
| 091 | u128divide | num, num | devide value | |value1,value2→value1/value2 | - |true |
| 092 | u128mul | num, num | multiply value | |value1,value2→value1*value2 | - |true |
| 093 | u128mod | int, int | a % b | |value1,value2→value1%value2 |double |true |
| 094 | u128xor | int, int | a ^ b | |value1,value2→value1^value2 |double |true |
| 095 | u128inv | num | !a | |value→!value | - |true |
| 096     | u256divide       | num, num        | devide value                                                 |                  | value1,value2→value1/value2          | -                                   |true |
| 097     | u256mul          | num, num        | multiply value                                               |                  | value1,value2→value1*value2          | -                                   | true                    |
| 098     | u256mod          | int, int        | a % b                                                        |                  | value1,value2→value1%value2          | double                              | true                    |
| 099     | u256xor          | int, int        | a ^ b                                                        |                  | value1,value2→value1^value2          | double                              | true                    |
| 100     | u256inv          | num             | !a                                                           |                  | value→!value                         | -                                   | true                    |
| 101     | u256lshift       | int, int        | a << val                                                     |                  | value1,value2→value1<<value2         | second parameter  < int32 max value | true                    |
| 102     | dinv             | num             | !a                                                           |                  | value→!value                         | -                                   | true                    |
| 103     | ddivide          | num, num        | devide value                                                 |                  | value1,value2→value1/value2          | -                                   | true                    |
| 104     | dmul             | num, num        | multiply value                                               |                  | value1,value2→value1*value2          | -                                   | True                    |
| 105     | u64or            | num             | a \|\| b                                                     |                  | value1,value2→value1\|\|value2       | -                                   |                         |
| 106     | u64and           | int             | a & b                                                        |                  | value1,value2→value1&value2          | double                              |                         |
| 107     | u128or           | num             | a \|\| b                                                     |                  | value1,value2→value1\|\|value2       | -                                   |                         |
| 108     | u128and          | int             | a & b                                                        |                  | value1,value2→value1&value2          | double                              |                         |
| 109     | u256or           | num             | a \|\| b                                                     |                  | value1,value2→value1\|\|value2       | -                                   |                         |
| 110     | u256and          | int             | a & b                                                        |                  | value1,value2→value1&value2          | double                              |                         |
| 111     | dor              | num             | a \|\| b                                                     |                  | value1,value2→value1\|\|value2       | -                                   |                         |
| 112     | iinc             | int, num        | a + increasing_value(e.g 1,2,3,4,5,6,7,8,9 etc). First parameter - is index of local(e.g 1,2,3,4), second - increasing value. In example we're increasing value in local#1 by 4, so if we have in local#1, for example value 6, it'll become 10 after instruction | iinc 1 4         | [No change]                          | -                                   |                         |
| 113     | i2d              | num,num         | convert int to double (two top values from stack)            | i2d              | value→result                         | -                                   |                         |
| 114     | i2u64            | num,num         | convert int to uint64 (two top values from stack)            | i2u64            | value→result                         | -                                   |                         |
| 115     | i2u128           | num,num         | convert int to uint128 (two top values from stack)           | i2u128           | value→result                         | -                                   |                         |
| 116     | i2u256           | num,num         | convert int to uint256 (two top values from stack)           | i2u256           | value→result                         | -                                   |                         |
| 117     | d2i              | num,num         | convert double to int (two top values from stack)            | d2i              | value→result                         | -                                   |                         |
| 118     | d2u64            | num,num         | convert double to uint64 (two top values from stack)         | d2u64            | value→result                         | -                                   |                         |
| 119     | d2u128           | num,num         | convert double to uint128 (two top values from stack)        | d2u128           | value→result                         | -                                   |                         |
| 120     | d2u256           | num,num         | convert double to uint256 (two top values from stack)        | d2u256           | value→result                         | -                                   |                         |
| 121     | u64_2u128        | num,num         | convert uint64 to uint128 (two top values from stack)        | u64_2u128        | value→result                         | -                                   |                         |
| 122     | u64_2u256        | num,num         | convert uint64 to uint256 (two top values from stack)        | u64_2u256        | value→result                         | -                                   |                         |
| 123     | u128_2u256       | num,num         | convert uint128 to uint256 (two top values from stack)       | u128_2u256       | value→result                         | -                                   |                         |
| 124     | u128lshift       | int, int        | a << val                                                     |                  | value1,value2→value1<<value2         | second parameter  < int32 max value |true |
| 125 | u64rshift | int, int | a << val | | value1,value2→value1<<value2 | second parameter  < int32 max value |true |
| 125 | u128rshift | int, int | a << val | | value1,value2→value1<<value2 | second parameter  < int32 max value |true |
| 126 | u256rshift | int, int | a << val | | value1,value2→value1<<value2 | second parameter  < int32 max value |true |
| | | | | | |  | |
| | | | | | |  | |
| | | | | | |  | |
| | | | | | | - | |
| | | | | | | - | |
| | | | | | | - | |
| | | | | | | - | |
| | | | | | | - | |
| | | | | | | - | |
| | | | | | | - | |
| | | | | | | - | |

[^1]: values array




# Vm Data Structures

| num  | name       | sizeof(class name)                 | note                                                         |
| ---- | ---------- | ---------------------------------- | ------------------------------------------------------------ |
| 1    | i32        | 40 bytes                           |                                                              |
| 2    | u64        | 8 bytes                            |                                                              |
| 3    | u128       | 80 bytes                           |                                                              |
| 4    | u256       | 96 bytes                           |                                                              |
| 5    | d64        | 40 bytes                           | number of decimal places is 4(due c++'s converting from string to double) |
| 6    | boolean    | 40 bytes                           |                                                              |
| 7    | collection | sum of sizes all structures inside |                                                              |
| 8    | str        | 1 byte * length (ASCII)            |                                                              |
| 9    | Object     | 40 bytes                           |                                                              |

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





# Update for structures and instructions

#### 04.07.22

>Each instruction means starts with types name:
>
>- i - integer
>- u64 - uint64_t
>- u128 - uint128_t
>- u256 - uint256_t
>- b - bool
>- c - collection
>- d - double
>- st - string 
> 

# Example of program bytecode(decimals)

```c++
const int program[] = {
    PSH, 5,
    PSH, 6,
    ADD,
    POP,
    HLT
};
```
