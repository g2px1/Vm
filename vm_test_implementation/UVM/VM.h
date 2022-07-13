//
// Created by Kirill Zhukov on 02.07.2022.
//

#ifndef VM_TEST_IMPLEMENTATION_VM_H
#define VM_TEST_IMPLEMENTATION_VM_H
#include "stack"
#include "iostream"
#include <cstdlib>
#include "DataTypes/Object.h"
//#include "DataTypes/u256.h"
//#include "DataTypes/u128.h"
//#include "DataTypes/u64.h"
//#include "DataTypes/i32.h"
//#include "DataTypes/d64.h"
//#include "DataTypes/boolean.h"
//#include "DataTypes/str.h"
//#include "DataTypes/collection.h"

#define PUSH(vm, v) vm->stack[++vm->sp] = v // push object on top of the stack
#define POP(vm)     vm->stack[vm->sp--]     // pop object from top of the stack
#define NCODE(vm)   vm->code[vm->pc++]      // get next bytecode

class VM {
public:
    inline explicit VM(uint16_t contractSize) : contract_size(contractSize) {
        if (contractSize > 25536) throw std::overflow_error("size of contract should be lower then 25536 bytes");
        this->contract_size = contractSize;
    }

//    static void run(std::unique_ptr<VM> vm);
    uint16_t contract_size;
private:
    uint8_t* stack = (uint8_t*)malloc(24576);
    uint8_t* locals = (uint8_t*) malloc(16); // local storage. it can store now 16 variables
    uint8_t program_counter;
    uint8_t stack_pointer = -1;
    void *frame_pointer;
};


#endif //VM_TEST_IMPLEMENTATION_VM_H
