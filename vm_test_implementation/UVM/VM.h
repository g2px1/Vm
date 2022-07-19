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
    inline void swap(Object *r, Object *s){
        Object temp = *r;
        *r = *s;
        *s = temp;
    }

    inline void remove_from_locals(Registers &reg, Object &obj){
        reg.erase(std::remove(reg.begin(), reg.end(), obj), reg.end());
    }

    inline Object copy(Object &obj) {
        Object object;
        object.object = obj.object;
        object.type = obj.type;
        return object;
    }

    inline bool stringContains(std::string &str, char c) {
        return ((str.find(c) != std::string::npos));
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

    inline static void VMRun(VM *vm, boost::json::array &stack_val) {
        boost::json::array::iterator it = stack_val.begin();
        void *ddt[] = {
                &&ldc,
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
                &&go_to
        }; // Direct Threading Table
        void **pc = ddt;
        goto **(pc++);


        ldc: {
            vm->stack.emplace_back(Object(vm->uniqueConstantPool.loadReference(boost::json::value_to<int>(*(++it)))));
            vm->ip++;
            goto *ddt[(++it)->as_int64()];
        };

        ostore_0: {
            if(std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
                throw std::logic_error("Registers are full");
            vm->locals[0] = vm->stack.back();
            vm->stack.pop_back();
            vm->ip++;
            goto *ddt[(++it)->as_int64()];
        };

        ostore_1: {
            if(std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
                throw std::logic_error("Registers are full");
            vm->locals[1] = vm->stack.back();
            vm->stack.pop_back();
            vm->ip++;
            goto *ddt[(++it)->as_int64()];
        };

        ostore_2: {
            if(std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
                throw std::logic_error("Registers are full");
            vm->locals[2] = vm->stack.back();
            vm->stack.pop_back();
            vm->ip++;
            goto *ddt[(++it)->as_int64()];
        };

        ostore_3: {
            if(std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
                throw std::logic_error("Registers are full");
            vm->locals[3] = vm->stack.back();
            vm->stack.pop_back();
            vm->ip++;
            goto *ddt[(++it)->as_int64()];
        };

        oload_0:{
            if (std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
                throw std::logic_error("Registers are full");
            vm->stack.emplace_back(vm->locals[0]);
            vm::remove_from_locals(vm->locals, vm->locals[0]);
            vm->ip++;
            goto *ddt[(++it)->as_int64()];
        };

        oload_1:{
            if (std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
                throw std::logic_error("Registers are full");
            vm->stack.emplace_back(vm->locals[1]);
            vm::remove_from_locals(vm->locals, vm->locals[1]);
            vm->ip++;
            goto *ddt[(++it)->as_int64()];
        };

        oload_2:{
            if (std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
                throw std::logic_error("Registers are full");
            vm->stack.emplace_back(vm->locals[2]);
            vm::remove_from_locals(vm->locals, vm->locals[2]);
            vm->ip++;
            goto *ddt[(++it)->as_int64()];
        };

        oload_3:{
            if (std::count_if(vm->locals.begin(), vm->locals.end(), null_object) == 0)
                throw std::logic_error("Registers are full");
            vm->stack.emplace_back(vm->locals[3]);
            vm::remove_from_locals(vm->locals, vm->locals[3]);
            vm->ip++;
            goto *ddt[(++it)->as_int64()];
        };

        swap:{
            vm::swap(&(vm->stack.back()), &(vm->stack[vm->stack.size()-2]));
            vm->ip++;
            goto *ddt[(++it)->as_int64()];
        };

        swap_references:{
            vm::swap(&(vm->stack[vm->stack.size() - (++it)->as_int64()]), &(vm->stack[vm->stack.size() - (++it)->as_int64()]));
            vm->ip++;
            goto *ddt[(++it)->as_int64()];
        };

        go_to:{
            vm->ip++;
            std::advance(it, -((vm->ip)-(++it)->as_int64()));
            goto *ddt[(it)->as_int64()];
        };

        iadd:{
            vm->ip++;
            (i32)(*(vm->stack.end()-=2)) += (i32)(vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u64add:{
            vm->ip++;
            (u64)(*(vm->stack.end()-=2)) += (u64)(vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u128add:{
            vm->ip++;
            (u128)(*(vm->stack.end()-=2)) += (u128)(vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u256add:{
            vm->ip++;
            (u256)(*(vm->stack.end()-=2)) += (u256)(vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        dadd:{
            vm->ip++;
            (d64)(*(vm->stack.end()-=2)) += (d64)(vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        isub:{
            vm->ip++;
            (i32)(*(vm->stack.end()-=2)) -= (i32)(vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u64sub:{
            vm->ip++;
            (u64)(*(vm->stack.end()-=2)) -= (u64)(vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u128sub:{
            vm->ip++;
            (u128)(*(vm->stack.end()-=2)) -= (u128)(vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u256sub:{
            vm->ip++;
            (u256)(*(vm->stack.end()-=2)) -= (u256)(vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        dsub:{
            vm->ip++;
            (d64)(*(vm->stack.end()-=2)) -= (d64)(vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        idivide:{
            vm->ip++;
            (i32)(*(vm->stack.end()-=2)) /= (i32)(vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u64divide:{
            vm->ip++;
            (u64)(*(vm->stack.end()-=2)) /= (u64) (vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u128divide:{
            vm->ip++;
            (u128)(*(vm->stack.end()-=2)) /= (u128) (vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u256divide:{
            vm->ip++;
            (u256)(*(vm->stack.end()-=2)) /= (u256) (vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        ddivide:{
            vm->ip++;
            (d64)(*(vm->stack.end()-=2)) /= (d64)(vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        imul:{
            vm->ip++;
            (i32)(*(vm->stack.end()-=2)) *= (i32) (vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u64mul:{
            vm->ip++;
            (u64)(*(vm->stack.end()-=2)) *= (u64) (vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u128mul:{
            vm->ip++;
            (u128)(*(vm->stack.end()-=2)) *= (u128) (vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u256mul:{
            vm->ip++;
            (u256)(*(vm->stack.end()-=2)) *= (u256) (vm->stack.back());
            vm->stack.pop_back();
            goto
            *ddt[(++it)->as_int64()];
        };

        dmul:{
            vm->ip++;
            (d64)(*(vm->stack.end()-=2)) *= (d64) (vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        imod: {
            vm->ip++;
            (i32)(*(vm->stack.end()-=2)) %= (i32) (vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u64mod:{
            vm->ip++;
            (u64)(*(vm->stack.end()-=2)) %= (u64) (vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u128mod:{
            vm->ip++;
            (u128)(*(vm->stack.end()-=2)) %= (u128) (vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u256mod:{
            vm->ip++;
            (u256)(*(vm->stack.end()-=2)) %= (u256) (vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        ixor:{
            vm->ip++;
            (i32) (*(vm->stack.end()-=2)) ^= (i32) (vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u64xor:{
            vm->ip++;
            (u64)(*(vm->stack.end()-=2)) ^= (u64) (vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u128xor:{
            vm->ip++;
            (u128)(*(vm->stack.end()-=2)) ^= (u128) (vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u256xor:{
            vm->ip++;
            (u256)(*(vm->stack.end()-=2)) ^= (u256) (vm->stack.back());
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        iinv:{
            vm->ip++;
            !(i32)(*(vm->stack.end()-=2));
            goto *ddt[(++it)->as_int64()];
        };

        u64inv: {
            vm->ip++;
            !(u64)(*(vm->stack.end()-=2));
            goto *ddt[(++it)->as_int64()];
        };

        u128inv:{
            vm->ip++;
            !(u128)(*(vm->stack.end()-=2));
            goto *ddt[(++it)->as_int64()];
        };

        u256inv:{
            vm->ip++;
            (u256)(*(vm->stack.end()-=2)) *= (u256) (vm->stack.back());
            goto *ddt[(++it)->as_int64()];
        };

        dinv:{
            vm->ip++;
            (d64)(*(vm->stack.end()-=2)) *= (d64) (vm->stack.back());
            goto *ddt[(++it)->as_int64()];
        };

        ilshift:{
            vm->ip++;
            (i32)(*(vm->stack.end()-=2)) <<= ((i32) (vm->stack.back())).value;
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u64lshift:{
            vm->ip++;
            (u64)(*(vm->stack.end()-=2)) <<= ((i32) (vm->stack.back())).value;
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u128lshift:{
            vm->ip++;
            (u128)(*(vm->stack.end()-=2)) <<= ((i32) (vm->stack.back())).value;
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u256lshift:{
            vm->ip++;
            (u256) (*(vm->stack.end()-=2)) <<= ((i32) (vm->stack.back())).value;
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        irshift:{
            vm->ip++;
            (i32) (*(vm->stack.end()-=2)) >>= ((i32) (vm->stack.back())).value;
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u64rshift:{
            vm->ip++;
            (u64) (*(vm->stack.end()-=2)) >>= ((i32) (vm->stack.back())).value;
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u128rshift:{
            vm->ip++;
            (u128) (*(vm->stack.end()-=2)) >>= ((i32) (vm->stack.back())).value;
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u256rshift:{
            vm->ip++;
            (u256) (*(vm->stack.end()-=2)) >>= ((i32) (vm->stack.back())).value;
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        pop:{
            vm->ip++;
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        dup:{
            vm->ip++;
            vm->stack.emplace_back(vm::copy(vm->stack.back()));
            goto *ddt[(++it)->as_int64()];
        };

        ior:{
            vm->ip++;
            (*(vm->stack.end()-=2)) = boolean((i32) (*(vm->stack.end()-=2)) || ((i32) (vm->stack.back())).value);
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u64or:{
            vm->ip++;
            (*(vm->stack.end()-=2)) = boolean((u64) (*(vm->stack.end()-=2)) || ((u64) (vm->stack.back())).value);
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u128or:{
            vm->ip++;
            (*(vm->stack.end()-=2)) = boolean((u128) (*(vm->stack.end()-=2)) || ((u128) (vm->stack.back())).value);
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u256or:{
            vm->ip++;
            (*(vm->stack.end()-=2)) = boolean((u256) (*(vm->stack.end()-=2)) || ((u256) (vm->stack.back())).value);
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        dor:{
            vm->ip++;
            (*(vm->stack.end()-=2)) = boolean((d64) (*(vm->stack.end()-=2)) || ((d64) (vm->stack.back())).value);
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        iand:{
            vm->ip++;
            (*(vm->stack.end()-=2)) = boolean((i32) (*(vm->stack.end()-=2)) && ((i32) (vm->stack.back())).value);
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u64and:{
            vm->ip++;
            (*(vm->stack.end()-=2)) = boolean((u64) (*(vm->stack.end()-=2)) && ((u64) (vm->stack.back())).value);
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u128and:{
            vm->ip++;
            (*(vm->stack.end()-=2)) = boolean((u128) (*(vm->stack.end()-=2)) && ((u128) (vm->stack.back())).value);
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        u256and:{
            vm->ip++;
            (*(vm->stack.end()-=2)) = boolean((u256) (*(vm->stack.end()-=2)) && ((u256) (vm->stack.back())).value);
            vm->stack.pop_back();
            goto *ddt[(++it)->as_int64()];
        };

        iconst_0:{
            vm->ip++;
            vm->stack.emplace_back(i32(0));
            goto *ddt[(++it)->as_int64()];
        };

        iconst_1:{
            vm->ip++;
            vm->stack.emplace_back(i32(1));
            goto *ddt[(++it)->as_int64()];
        };

        iconst_2:{
            vm->ip++;
            vm->stack.emplace_back(i32(2));
            goto *ddt[(++it)->as_int64()];
        };

        iconst_3:{
            vm->ip++;
            vm->stack.emplace_back(i32(3));
            goto *ddt[(++it)->as_int64()];
        };

        iconst_4:{
            vm->ip++;
            vm->stack.emplace_back(i32(4));
            goto *ddt[(++it)->as_int64()];
        };

        iconst_5:{
            vm->ip++;
            vm->stack.emplace_back(i32(5));
            goto *ddt[(++it)->as_int64()];
        };

        u64const_0:{
            vm->ip++;
            vm->stack.emplace_back(u64(0));
            goto *ddt[(++it)->as_int64()];
        };

        u64const_1:{
            vm->ip++;
            vm->stack.emplace_back(u64(1));
            goto *ddt[(++it)->as_int64()];
        };

        u64const_2:{
            vm->ip++;
            vm->stack.emplace_back(u64(2));
            goto *ddt[(++it)->as_int64()];
        };

        u64const_3:{
            vm->ip++;
            vm->stack.emplace_back(u64(3));
            goto *ddt[(++it)->as_int64()];
        };

        u64const_4:{
            vm->ip++;
            vm->stack.emplace_back(u64(4));
            goto *ddt[(++it)->as_int64()];
        };

        u64const_5:{
            vm->ip++;
            vm->stack.emplace_back(u64(5));
            goto *ddt[(++it)->as_int64()];
        };

        u128const_0: {
            vm->ip++;
            vm->stack.emplace_back(u128(0));
            goto *ddt[(++it)->as_int64()];
        };

        u128const_1: {
            vm->ip++;
            vm->stack.emplace_back(u128(1));
            goto *ddt[(++it)->as_int64()];
        };

        u128const_2: {
            vm->ip++;
            vm->stack.emplace_back(u64(2));
            goto *ddt[(++it)->as_int64()];
        };

        u128const_3: {
            vm->ip++;
            vm->stack.emplace_back(u128(3));
            goto *ddt[(++it)->as_int64()];
        };

        u128const_4:{
            vm->ip++;
            vm->stack.emplace_back(u128(4));
            goto
            *ddt[(++it)->as_int64()];
        };

        u128const_5:{
            vm->ip++;
            vm->stack.emplace_back(u128(5));
            goto *ddt[(++it)->as_int64()];
        };

        u256const_0:{
            vm->ip++;
            vm->stack.emplace_back(u256(0));
            goto *ddt[(++it)->as_int64()];
        };

        u256const_1:{
            vm->ip++;
            vm->stack.emplace_back(u256(1));
            goto *ddt[(++it)->as_int64()];
        };

        u256const_2:{
            vm->ip++;
            vm->stack.emplace_back(u256(2));
            goto *ddt[(++it)->as_int64()];
        };

        u256const_3:{
            vm->ip++;
            vm->stack.emplace_back(u256(3));
            goto
            *ddt[(++it)->as_int64()];
        };

        u256const_4:{
            vm->ip++;
            vm->stack.emplace_back(u256(4));
            goto *ddt[(++it)->as_int64()];
        };

        u256const_5:{
            vm->ip++;
            vm->stack.emplace_back(u256(5));
            goto*ddt[(++it)->as_int64()];
        };

        if_acmpeq:{
            vm->ip++;
            if(vm->stack.back() == (*(vm->stack.end()-=2)))
                goto *ddt[(it+=2)->as_int64()];

            if ((++it)->as_int64() < vm->ip)
                it += (vm->ip - (++it)->as_int64());
            else
                std::advance(it, -((vm->ip)-(++it)->as_int64()));

            goto *ddt[it->as_int64()];
        };

        if_acmpne:{
            vm->ip++;
            if (vm->stack.back() != (*(vm->stack.end() -= 2)))
                goto *ddt[(it += 2)->as_int64()];

            if ((++it)->as_int64() < vm->ip)
                it += (vm->ip - (++it)->as_int64());
            else
                std::advance(it, -((vm->ip) - (++it)->as_int64()));

            goto*ddt[it->as_int64()];
        };

        if_icmpeq:{
            vm->ip++;
            if ((vm->stack.back().type != 1) ? u256(*vm->stack.back().object) == u256(*(*(vm->stack.end() -= 2)).object) : i32(*vm->stack.back().object) == i32(*((*(vm->stack.end() -= 2)).object)))
                goto *ddt[(it += 2)->as_int64()];

            if ((++it)->as_int64() < vm->ip)
                it += (vm->ip - (++it)->as_int64());
            else
                std::advance(it, -((vm->ip) - (++it)->as_int64()));

            goto *ddt[it->as_int64()];
        };

        if_icmpge:{
            vm->ip++;
            if ((vm->stack.back().type != 1) ? u256(*vm->stack.back().object) >= u256(*(*(vm->stack.end() -= 2)).object) : i32(*vm->stack.back().object) >= i32(*((*(vm->stack.end() -= 2)).object)))
                goto *ddt[(it += 2)->as_int64()];

            if ((++it)->as_int64() < vm->ip)
                it += (vm->ip - (++it)->as_int64());
            else
                std::advance(it, -((vm->ip) - (++it)->as_int64()));

            goto *ddt[it->as_int64()];
        };

        if_icmpgt:{
            vm->ip++;
            if ((vm->stack.back().type != 1) ? u256(*vm->stack.back().object) > u256(*(*(vm->stack.end() -= 2)).object) : i32(*vm->stack.back().object) > i32(*((*(vm->stack.end() -= 2)).object)))
                goto *ddt[(it += 2)->as_int64()];

            if ((++it)->as_int64() < vm->ip)
                it += (vm->ip - (++it)->as_int64());
            else
                std::advance(it, -((vm->ip) - (++it)->as_int64()));

            goto *ddt[it->as_int64()];
        };

        if_icmple:{
            vm->ip++;
            if ((vm->stack.back().type != 1) ? u256(*vm->stack.back().object) <= u256(*(*(vm->stack.end() -= 2)).object)
                                             : i32(*vm->stack.back().object) <= i32(*((*(vm->stack.end() -= 2)).object)))
                goto *ddt[(it += 2)->as_int64()];

            if ((++it)->as_int64() < vm->ip)
                it += (vm->ip - (++it)->as_int64());
            else
                std::advance(it, -((vm->ip) - (++it)->as_int64()));

            goto *ddt[it->as_int64()];
        };

        if_icmplt:{
            vm->ip++;
            if ((vm->stack.back().type != 1) ? u256(*vm->stack.back().object) < u256(*(*(vm->stack.end() -= 2)).object)
                                             : i32(*vm->stack.back().object) <
                                               i32(*((*(vm->stack.end() -= 2)).object)))
                goto *ddt[(it += 2)->as_int64()];

            if ((++it)->as_int64() < vm->ip)
                it += (vm->ip - (++it)->as_int64());
            else
                std::advance(it, -((vm->ip) - (++it)->as_int64()));

            goto *ddt[it->as_int64()];
        };

        if_icmpne:{
            vm->ip++;
            if ((vm->stack.back().type != 1) ? u256(*vm->stack.back().object) != u256(*(*(vm->stack.end() -= 2)).object)
                                             : i32(*vm->stack.back().object) !=
                                               i32(*((*(vm->stack.end() -= 2)).object)))
                goto *ddt[(it += 2)->as_int64()];

            if ((++it)->as_int64() < vm->ip)
                it += (vm->ip - (++it)->as_int64());
            else
                std::advance(it, -((vm->ip) - (++it)->as_int64()));

            goto *ddt[it->as_int64()];
        };

        ifeq:{
            vm->ip++;
            if (i32(*vm->stack.back().object) == i32(0))
                goto *ddt[(it += 2)->as_int64()];

            if ((++it)->as_int64() < vm->ip)
                it += (vm->ip - (++it)->as_int64());
            else
                std::advance(it, -((vm->ip) - (++it)->as_int64()));

            goto *ddt[it->as_int64()];
        };

        ifge: {
            vm->ip++;
            if (i32(*vm->stack.back().object) >= i32(0))
                goto *ddt[(it += 2)->as_int64()];

            if ((++it)->as_int64() < vm->ip)
                it += (vm->ip - (++it)->as_int64());
            else
                std::advance(it, -((vm->ip) - (++it)->as_int64()));

            goto *ddt[it->as_int64()];
        };

        ifgt:{
            vm->ip++;
            if (i32(*vm->stack.back().object) > i32(0))
                goto *ddt[(it += 2)->as_int64()];

            if ((++it)->as_int64() < vm->ip)
                it += (vm->ip - (++it)->as_int64());
            else
                std::advance(it, -((vm->ip) - (++it)->as_int64()));

            goto *ddt[it->as_int64()];
        };

        ifle:{
            vm->ip++;
            if (i32(*vm->stack.back().object) <= i32(0))
                goto *ddt[(it += 2)->as_int64()];

            if ((++it)->as_int64() < vm->ip)
                it += (vm->ip - (++it)->as_int64());
            else
                std::advance(it, -((vm->ip) - (++it)->as_int64()));

            goto *ddt[it->as_int64()];
        };

        ifne:{
            vm->ip++;
            if (i32(*vm->stack.back().object) <= i32(0))
                goto *ddt[(it += 2)->as_int64()];

            if ((++it)->as_int64() < vm->ip)
                it += (vm->ip - (++it)->as_int64());
            else
                std::advance(it, -((vm->ip) - (++it)->as_int64()));

            goto *ddt[it->as_int64()];
        };

        ifnonnull:{
            vm->ip++;
            if (!vm->stack.back().isNull())
                goto *ddt[(it += 2)->as_int64()];

            if ((++it)->as_int64() < vm->ip)
                it += (vm->ip - (++it)->as_int64());
            else
                std::advance(it, -((vm->ip) - (++it)->as_int64()));

            goto *ddt[it->as_int64()];
        };

        ifnull: {
            vm->ip++;
            if (vm->stack.back().isNull())
                goto *ddt[(it += 2)->as_int64()];

            if ((++it)->as_int64() < vm->ip)
                it += (vm->ip - (++it)->as_int64());
            else
                std::advance(it, -((vm->ip) - (++it)->as_int64()));

            goto *ddt[it->as_int64()];
        };

        nop: {
            vm->ip++;
            goto *ddt[(++it)->as_int64()];
        };

        collectionlength:{
            vm->ip++;
            if(vm->stack.back().type == 7)
                vm->stack.emplace_back(i32(((collection) vm->stack.back()).size()));
            else
                throw std::logic_error("not a collection");
            goto *ddt[(++it)->as_int64()];
        };

        dconst_0:{
            vm->ip++;
            vm->stack.emplace_back(d64(0.0));
            goto *ddt[(++it)->as_int64()];
        };

        dconst_1:{
            vm->ip++;
            vm->stack.emplace_back(d64(1.0));
            goto *ddt[(++it)->as_int64()];
        };

        iinc:{
            vm->ip++;
            *(vm->locals.begin() += (++it)->as_int64()) = i32((i32) *(vm->locals.begin() += (it)->as_int64()) + i32((++it)->as_int64()));
            goto *ddt[(++it)->as_int64()];
        };

        i2d:{
            vm->ip++;
            *(vm->stack.end()) = d64(vm->stack.back());
            goto *ddt[(++it)->as_int64()];
        };

        i2u64:{
            vm->ip++;
            *(vm->stack.end()) = u64(vm->stack.back());
            goto *ddt[(++it)->as_int64()];
        };

        i2u128:{
            vm->ip++;
            *(vm->stack.end()) = u128(vm->stack.back());
            goto *ddt[(++it)->as_int64()];
        };

        i2u256:{
            vm->ip++;
            *(vm->stack.end()) = u256(vm->stack.back());
            goto *ddt[(++it)->as_int64()];
        };

        d2i:{
            vm->ip++;
            *(vm->stack.end()) = d64(vm->stack.back());
            goto *ddt[(++it)->as_int64()];
        };

        d2u64:{
            vm->ip++;
            *(vm->stack.end()) = u64(vm->stack.back());
            goto *ddt[(++it)->as_int64()];
        };

        d2u128:{
            vm->ip++;
            *(vm->stack.end()) = u128(vm->stack.back());
            goto *ddt[(++it)->as_int64()];
        };

        d2u256:{
            vm->ip++;
            *(vm->stack.end()) = u256(vm->stack.back());
            goto *ddt[(++it)->as_int64()];
        };

        u64_2u128:{
            vm->ip++;
            *(vm->stack.end()) = u128(vm->stack.back());
            goto *ddt[(++it)->as_int64()];
        };

        u64_2u256:{
            vm->ip++;
            *(vm->stack.end()) = u256(vm->stack.back());
            goto *ddt[(++it)->as_int64()];
        };

        u128_2u256:{
            vm->ip++;
            *(vm->stack.end()) = u256(vm->stack.back());
            goto *ddt[(++it)->as_int64()];
        };

        u64inc:{
            vm->ip++;
            *(vm->locals.begin() += (++it)->as_int64()) = u64(u64(*(vm->locals.begin() += (it)->as_int64())) + u64(boost::json::value_to<uint64_t>(*(++it))));
            goto *ddt[(++it)->as_int64()];
        };

        u128inc:{
            vm->ip++;
            *(vm->locals.begin() += (++it)->as_int64()) = u128(u64(*(vm->locals.begin() += (it)->as_int64())) + u128(boost::json::value_to<boost::multiprecision::uint128_t>(*(++it))));
            goto *ddt[(++it)->as_int64()];
        };

        u256inc:{
            vm->ip++;
            *(vm->locals.begin() += (++it)->as_int64()) = u256(u64(*(vm->locals.begin() += (it)->as_int64())) + u256(boost::json::value_to<boost::multiprecision::uint256_t>(*(++it))));
            goto *ddt[(++it)->as_int64()];
        };
    }

    inline static Object invokeAdditionalFunction(VM *vm){
        return Object();
    }

    template<class T>
    inline T returnObjectWithType(Object &obj){
        switch (obj.type) {
            case 1:
                return (i32) obj;
                break;
            case 2:
                return (u64) obj;
                break;
            case 3:
                return (u128) obj;
                break;
            case 4:
                return (u256) obj;
                break;
            case 5:
                return (d64) obj;
                break;
            case 6:
                return (boolean) obj;
                break;
            case 7:
                return (collection) obj;
                break;
            case 8:
                return (str) obj;
                break;
            default:
                return (Object) obj;
                break;
        }
    }

    static bool null_object(Object &obj) {
        return (obj.object == nullptr);
    }

    uint16_t contract_size;
    UniqueConstantPool uniqueConstantPool;
private:
    std::vector<Object> stack;
    Registers locals{}; // local storage
    uint32_t ip = 0;
};


#endif //VM_TEST_IMPLEMENTATION_VM_H
