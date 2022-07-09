#include <iostream>
#include "UVM/DataTypes/Object.h"
#include "UVM/DataTypes/u128.h"
#include "UVM/DataTypes/u256.h"
#include "UVM/DataTypes/boolean.h"
#include "UVM/DataTypes/d64.h"
#include "UVM/DataTypes/str.h"
#include "boost/multiprecision/cpp_int.hpp"
#include "UVM/DataTypes/collection.h"

int main() {
//    std::string str = R"({"test": "1"})";
//    std::string str1 = R"({"test": "2"})";
//    Object object = Object(str);
//    Object object1 = Object(str1);
//    Object object2 = u128();
//    std::cout << object.toString() << std::endl << sizeof(object1);

//    std::string str = "testaba";
//
//    str.erase(remove(str.begin(), str.end(), "aba"), str.end());
//
//    std::cout << str;

    u128 u = u128(pow(2,2));
    u256 u2 = u256(pow(2,20));
    boolean boolean1 = boolean(true);
    d64 d1 = d64(1021.1012);
    collection collection;

    collection.push_back(u);
    collection.push_back(boolean1);
    collection.push_back(d1);

//    std::cout << collection.find(u2);

    std::cout << u << std::endl << u2 << std::endl;
    std::cout << (u2 > u);

//    boost::multiprecision::uint128_t uint128("2132312");
//
//    std::string str2 = "10.432523453";
//    d64 d = d64(str2);
//    std::cout << d << std::endl;

    return 0;
}
