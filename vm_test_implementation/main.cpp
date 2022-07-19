#include <iostream>
#include "vector"
#include "map"
#include "optional"
#include <boost/json/src.hpp>
#include <boost/json/value.hpp>
#include <boost/json/value_to.hpp>
#include "boost/json/value_from.hpp"
#include "boost/json/array.hpp"
#include "boost/unordered_map.hpp"
#include "boost/multiprecision/cpp_int.hpp"
#include "string"
#include "UVM/DataTypes/Object.h"
#include "UVM/DataTypes/u128.h"
#include "UVM/DataTypes/boolean.h"
#include "UVM/DataTypes/i32.h"
#include "UVM/DataTypes/u64.h"
#include "UVM/DataTypes/u256.h"
#include "UVM/DataTypes/d64.h"
#include "UVM/DataTypes/str.h"
#include "UVM/DataTypes/collection.h"
#include "UVM/DataTypes/Pools/UniqueConstantPool.h"
#include "stack"
#include "array"
#include <algorithm>
#include <iterator>
#include "timeTest/LogDuration.h"

void pop(std::vector<int> &vec) {
    vec.pop_back();
}

void print_vector(std::vector<Object> &vector) {
    for(int i = 0; i < vector.size(); i++)
        std::cout << "\"" << i << "\" = " << vector[i] << std::endl;
    std::cout << "---------------------" << std::endl;
}

void swap(Object *r, Object *s){
    Object temp = *r;
    *r = *s;
    *s = temp;
}

void swapInt(int *r, int *s){
    int temp = *r;
    *r = *s;
    *s = temp;
}

int main() {
    Object object = Object();
    object.setObject("test");
    Object object1 = Object();
    object1.setObject("test2");
    u128 u1 = u128(111);

//    std::vector<Object> vector1 = {object, object1, u1};
//
//    print_vector(vector1);
//    swap(&vector1[0], &vector1[vector1.size()-1]);
//    print_vector(vector1);

//    std::cout << vector1[vector1.size()-1] << std::endl;
//    std::vector<int> vector(1e7, 0);
//    {
//        LogDuration logDuration = LogDuration("test");
//        for(int i = 0; i < vector.size(); i++)
//            swapInt(&vector[i], &vector[vector.size()-i]);
//    }
    boost::multiprecision::uint256_t d(111);
    boost::multiprecision::uint256_t b(2);
    uint64_t c = 2;
    std::cout << (d >> 2) << std::endl;
    return 0;
}