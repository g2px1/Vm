//
// Created by Kirill Zhukov on 02.07.2022.
//

#ifndef VM_TEST_IMPLEMENTATION_VM_H
#define VM_TEST_IMPLEMENTATION_VM_H
#include "stack"
#include "iostream"
#include <cstdlib>
#include "DataTypes/Object.h"
#include "DataTypes/u256.h"
#include "DataTypes/u128.h"
#include "DataTypes/u64.h"
#include "DataTypes/i32.h"
#include "DataTypes/d64.h"
#include "DataTypes/boolean.h"
#include "DataTypes/str.h"
#include "DataTypes/collection.h"
#include "DataTypes/Pools/UniqueConstantPool.h"

#define PUSH(vm, v) vm->stack[++vm->sp] = v // push object on top of the stack
#define POP(vm)     vm->stack[vm->sp--]     // pop object from top of the stack
#define NCODE(vm)   vm->code[vm->pc++]      // get next bytecode

class VM {
public:
    inline VM() = default;

    inline explicit VM(uint16_t contractSize, std::string &code) : contract_size(contractSize) {
        if (contractSize > 25536) throw std::overflow_error("size of contract should be lower then 25536 bytes");
        this->contract_size = contractSize;
        this->uniqueConstantPool = UniqueConstantPool(code);
    }

//    static void run(std::unique_ptr<VM> vm);

    uint16_t contract_size;
    UniqueConstantPool uniqueConstantPool;
private:
    Object* stack = (Object*)malloc(24576);
    Object* locals = (Object*) malloc(sizeof(Object) * 4); // local storage. it can store now 16 variables
    uint16_t ip; // instruction pointer
    uint16_t stack_pointer = -1;
    void *frame_pointer;
};


#endif //VM_TEST_IMPLEMENTATION_VM_H
