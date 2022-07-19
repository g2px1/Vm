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

inline Object copy(Object &obj) {
    Object object;
    object.object = obj.object;
    object.type = obj.type;
    return object;
}

int main() {
    Object object = Object();
    object.setObject("test");
    Object object1 = Object();
    object1.setObject("test2");
    u128 u1 = u128(111);
    Object object2 = Object();
    object2.setObject("2222");
    std::vector<Object> vector1 = {object, object1, u1, object, object1};

    std::vector<Object>::iterator it = vector1.begin();

//    std::cout << a << std::endl;

    return 0;
}