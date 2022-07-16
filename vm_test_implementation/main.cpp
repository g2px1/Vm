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

static bool null_object(Object &obj) {
//    return (obj.object == "NULL_OBJECT");
    return false;
}

int main() {
    Object object = Object();
    object.object = "test";
    Object object1 = Object();
    object1.object = "test2";
    auto *stack = new Object[1];
    *stack = object;
    std::cout << stack << *stack << std::endl;
    std::array<Object,4> array{};
    array[0] = Object("test");
    std::cout << "found: " << (std::find_if(array.begin(), array.end(), null_object) != array.end() ) << std::endl;
}