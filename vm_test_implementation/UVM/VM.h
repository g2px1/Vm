//
// Created by Kirill Zhukov on 02.07.2022.
//

#ifndef VM_TEST_IMPLEMENTATION_VM_H
#define VM_TEST_IMPLEMENTATION_VM_H
#include "stack"
#include "iostream"
#include <cstdlib>
#define PUSH(vm, v) vm->stack[++vm->sp] = v // push object on top of the stack
#define POP(vm)     vm->stack[vm->sp--]     // pop object from top of the stack
#define NCODE(vm)   vm->code[vm->pc++]      // get next bytecode

class VM {
public:
    VM(uint16_t contractSize);

//    static void run(std::unique_ptr<VM> vm);
    uint16_t contract_size;
private:
    uint8_t* stack = (uint8_t*)malloc(24576);
    uint8_t* locals = (uint8_t*) malloc(contract_size);
    uint8_t program_counter;
    uint8_t stack_pointer = -1;
    void *frame_pointer;
};


#endif //VM_TEST_IMPLEMENTATION_VM_H
