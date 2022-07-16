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
#include "boost/json/array.hpp"
#include "exception"

typedef std::array<Object, 4> Registers;

class VM {
public:
    inline VM() = default;

    inline explicit VM(uint16_t contractSize, std::string &code) : contract_size(contractSize) {
        if (contractSize > 25536) throw std::overflow_error("size of contract should be lower then 25536 bytes");
        this->contract_size = contractSize;
        this->uniqueConstantPool = UniqueConstantPool(code);
    }

    static void VMRun(VM *vm, boost::json::array &stack_val) {
        boost::json::array::iterator it = stack_val.begin();
        void *ddt[] = {
                &&ldc,
                &&stop,
                &&ostore_0,
                &&ostore_1,
                &&ostore_2,
                &&ostore_3,
        }; // Direct Threading Table
        void **pc = ddt;
        goto **(pc++);

        ldc: {
            vm->stack.push(Object(vm->uniqueConstantPool.loadReference(boost::json::value_to<int>(*(++it)))));
            goto *ddt[(++it)->as_int64()];
        };

        ostore_0: {
            if(std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
                throw std::logic_error("Registers are full");
            vm->locals[0] = vm->stack.top();
            vm->stack.pop();
        };

        ostore_1: {
            if(std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
                throw std::logic_error("Registers are full");
            vm->locals[1] = vm->stack.top();
            vm->stack.pop();
        };

        ostore_2: {
            if(std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
                throw std::logic_error("Registers are full");
            vm->locals[2] = vm->stack.top();
            vm->stack.pop();
        };

        ostore_3: {
            if(std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
                throw std::logic_error("Registers are full");
            vm->locals[3] = vm->stack.top();
            vm->stack.pop();
        };

//        u64store_0:{
//            if (std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
//                throw std::logic_error("Registers are full");
//            vm->locals[0] = (i32) vm->stack.top();
//            vm->stack.pop();
//        };
//
//        u64store_1:{
//            if (std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
//                throw std::logic_error("Registers are full");
//            vm->locals[1] = (i32) vm->stack.top();
//            vm->stack.pop();
//        };
//
//        u64store_2:{
//            if (std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
//                throw std::logic_error("Registers are full");
//            vm->locals[2] = (i32) vm->stack.top();
//            vm->stack.pop();
//        };
//
//        u64store_3:{
//            if (std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
//                throw std::logic_error("Registers are full");
//            vm->locals[3] = (i32) vm->stack.top();
//            vm->stack.pop();
//        };
//
//        u128store_0:{
//            if (std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
//                throw std::logic_error("Registers are full");
//            vm->locals[0] = (i32) vm->stack.top();
//            vm->stack.pop();
//        };
//
//        u128store_1:{
//            if (std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
//                throw std::logic_error("Registers are full");
//            vm->locals[1] = (i32) vm->stack.top();
//            vm->stack.pop();
//        };
//
//        u128store_2:{
//            if (std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
//                throw std::logic_error("Registers are full");
//            vm->locals[2] = (i32) vm->stack.top();
//            vm->stack.pop();
//        };
//
//        u128store_3:{
//            if (std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
//                throw std::logic_error("Registers are full");
//            vm->locals[3] = (i32) vm->stack.top();
//            vm->stack.pop();
//        };

        stop: {
            return;
        };
    }

    static bool null_object(Object &obj) {
        return (obj.object == "NULL_OBJECT");
    }

    uint16_t contract_size;
    UniqueConstantPool uniqueConstantPool;
private:
    std::stack<Object> stack;
    Registers locals{}; // local storage
};


#endif //VM_TEST_IMPLEMENTATION_VM_H
