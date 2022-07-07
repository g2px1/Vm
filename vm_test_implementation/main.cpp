#include <iostream>
#include "UVM/DataTypes/Object.h"
#include "UVM/DataTypes/u128.h"
#include "UVM/DataTypes/boolean.h"
//#include "boost/multiprecision/cpp_int.hpp"

#include "UVM/DataTypes/collection.h"

int main() {
    std::string str = R"({"test": "1"})";
    std::string str1 = R"({"test": "2"})";
//    Object object = Object(str);
//    Object object1 = Object(str1);
//    Object object2 = u128();
//    std::cout << object.toString() << std::endl << sizeof(object1);

//    std::string str = "testaba";
//
//    str.erase(remove(str.begin(), str.end(), "aba"), str.end());
//
//    std::cout << str;

    u128 u = u128(1231);
    boolean boolean1 = boolean(1);
    Object object = Object(1);
    collection collection;

    collection.push_back(u);
    collection.push_back(boolean1);
    collection.push_back(object);

//    std::cout << collection.getWithCast<u128>(0);

    return 0;
}
