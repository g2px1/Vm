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

typedef std::vector<Object> Registers;

namespace vm {
    void swap(Object *r, Object *s){
        Object temp = *r;
        *r = *s;
        *s = temp;
    }

    void remove_from_locals(Registers &reg, Object &obj){
        reg.erase(std::remove(reg.begin(), reg.end(), obj), reg.end());
    }
}

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
                &&oload_0,
                &&oload_1,
                &&oload_2,
                &&oload_3,
                &&swap,
                &&swap_references,
        }; // Direct Threading Table
        void **pc = ddt;
        goto **(pc++);

        ldc: {
            vm->stack.emplace_back(Object(vm->uniqueConstantPool.loadReference(boost::json::value_to<int>(*(++it)))));
            goto *ddt[(++it)->as_int64()];
        };

        ostore_0: {
            if(std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
                throw std::logic_error("Registers are full");
            vm->locals[0] = vm->stack.back();
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        ostore_1: {
            if(std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
                throw std::logic_error("Registers are full");
            vm->locals[1] = vm->stack.back();
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        ostore_2: {
            if(std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
                throw std::logic_error("Registers are full");
            vm->locals[2] = vm->stack.back();
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        ostore_3: {
            if(std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
                throw std::logic_error("Registers are full");
            vm->locals[3] = vm->stack.back();
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        oload_0:{
            if (std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
                throw std::logic_error("Registers are full");
            vm->stack.emplace_back(vm->locals[0]);
            vm::remove_from_locals(vm->locals, vm->locals[0]);
            goto *ddt[(++it)->as_int64()];
        };

        oload_1:{
            if (std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
                throw std::logic_error("Registers are full");
            vm->stack.emplace_back(vm->locals[1]);
            vm::remove_from_locals(vm->locals, vm->locals[1]);
            goto *ddt[(++it)->as_int64()];
        };

        oload_2:{
            if (std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
                throw std::logic_error("Registers are full");
            vm->stack.emplace_back(vm->locals[2]);
            vm::remove_from_locals(vm->locals, vm->locals[2]);
            goto *ddt[(++it)->as_int64()];
        };

        oload_3:{
            if (std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
                throw std::logic_error("Registers are full");
            vm->stack.emplace_back(vm->locals[3]);
            vm::remove_from_locals(vm->locals, vm->locals[3]);
            goto *ddt[(++it)->as_int64()];
        };

        swap:{
            vm::swap(&(vm->stack[vm->stack.size()-1]), &(vm->stack[vm->stack.size()-2]));
            goto *ddt[(++it)->as_int64()];
        };

        swap_references:{
            vm::swap(&(vm->stack[vm->stack.size() - (++it)->as_int64()]), &(vm->stack[vm->stack.size() - (++it)->as_int64()]));
            goto *ddt[(++it)->as_int64()];
        };

        stop: {
            return;
        };
    }

    static Object invokeAdditionalFunction(VM *vm){
        return Object();
    }

    static bool null_object(Object &obj) {
        return (obj.object == nullptr);
    }

    uint16_t contract_size;
    UniqueConstantPool uniqueConstantPool;
private:
    std::vector<Object> stack;
    Registers locals{}; // local storage
};


#endif //VM_TEST_IMPLEMENTATION_VM_H
