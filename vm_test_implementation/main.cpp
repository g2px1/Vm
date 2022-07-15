#include <iostream>
#include "vector"
#include "map"
#include "optional"
#include <boost/json/src.hpp>
#include <boost/json/value.hpp>
#include <boost/json/value_to.hpp>
#include "boost/json/value_from.hpp"
#include "boost/unordered_map.hpp"
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
#include <thread>
#include <future>


int main() {
//    Object object = Object();
//    object.object = "test";
//    u128 u1 = u128(111);
//    boolean boolean1 = boolean("true");
//    std::vector<Object> vector;
//    vector.emplace_back(object);
//    vector.emplace_back(boolean1);
//    vector.emplace_back(u1);
//    collection coll = collection(vector);
//    vector.emplace_back(coll);
//
//    std::cout << sizeof(UniqueConstantPool);


    void *code[] = {&&test1, &&test2, &&test3, &&end};
    void **pc = code;
    goto **(pc++);

    test1: {
        std::cout << "test1" << std::endl;
        goto **(pc++);
    };

    test2: {
        std::cout << "test2" << std::endl;
        goto **(pc++);
    };

    test3: {
        std::cout << "test3" << std::endl;
        goto **(pc++);
    };

    end: {return 0;};
}