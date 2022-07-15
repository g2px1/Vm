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

int main() {
    Object object = Object();
    object.object = "test";
    u128 u1 = u128(111);
    boolean boolean1 = boolean("true");
    std::vector<Object> vector;
    vector.emplace_back(object);
    vector.emplace_back(boolean1);
    vector.emplace_back(u1);

    collection coll = collection(vector);

    vector.emplace_back(coll);

    std::stringstream stringstream;
    stringstream << "[";
    for(int i = 0; i < vector.size(); i++) {
        switch (vector[i].type) {
            case 0:
                stringstream << (Object) vector[i];
                break;
            case 1:
                stringstream << (i32) vector[i];
                break;
            case 2:
                stringstream << (u64) vector[i];
                break;
            case 3:
                stringstream << (u128) vector[i];
                break;
            case 4:
                stringstream << (u256) vector[i];
                break;
            case 5:
                stringstream << (d64) vector[i];
                break;
            case 6:
                stringstream << (boolean) vector[i];
                break;
            case 7:
                stringstream << (collection) vector[i];
                break;
            case 8:
                stringstream << (str) vector[i];
                break;
            default:
                break;
        }
        (i != vector.size() - 1) ? stringstream <<  ',' : stringstream << ']';
    }

    std::string str = R"({"functions": [{"test": [1,2,3]}, {"test2": [1,2,3]}]})";
    std::cout << str << std::endl;
    boost::json::value value = boost::json::parse(str);

    UniqueConstantPool uniqueConstantPool = UniqueConstantPool(str);

    std::string values = stringstream.str();
    uniqueConstantPool.deserialize(values);

    std::string functionName = "test";
    std::optional<std::vector<uint16_t>> vector2 = uniqueConstantPool.loadFunction(functionName);

    if(vector2.has_value())
        std::cout << vector2.value()[2] << std::endl;
    else
        std::cout << "no value" << std::endl;

    std::cout << uniqueConstantPool.serialize() << std::endl;

    return 0;
}
