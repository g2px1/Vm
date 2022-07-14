#include <iostream>
#include "vector"
#include "map"
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

    boost::json::value jv = boost::json::parse(stringstream.str());
    std::cout << jv << std::endl;
    std::vector<Object> vector1;
    for(int i = 0; i < jv.as_array().size(); i++) {
        switch (jv.as_array()[i].as_object()["type"].as_int64()) {
            case 0:
                vector1.emplace_back(Object(serialize(jv.as_array()[i].at("value"))));
                break;
            case 1:
                vector1.emplace_back(i32(serialize(jv.as_array()[i].at("value"))));
                break;
            case 2:
                vector1.emplace_back(u64(serialize(jv.as_array()[i].at("value"))));
                break;
            case 3:
                vector1.emplace_back(u128(serialize(jv.as_array()[i].at("value"))));
                break;
            case 4:
                vector1.emplace_back(u256(serialize(jv.as_array()[i].at("value"))));
                break;
            case 5:
                vector1.emplace_back(d64(serialize(jv.as_array()[i].at("value"))));
                break;
            case 6:
                vector1.emplace_back(boolean(serialize(jv.as_array()[i].at("value"))));
                break;
            case 7:
                vector1.emplace_back(collection(boost::json::serialize(jv.as_array()[i].at("value"))));
                break;
            case 8:
                vector1.emplace_back(str(serialize(jv.as_array()[i].as_object()["value"])));
                break;
            default:
                break;
        }
        (i != vector.size() - 1) ? stringstream <<  ',' : stringstream << ']';
    }

    std::stringstream stringstream1;
    stringstream1 << "[";
    for(int i = 0; i < vector1.size(); i++) {
        switch (vector1[i].type) {
            case 0:
                stringstream1 << (Object) vector1[i];
                break;
            case 1:
                stringstream1 << (i32) vector1[i];
                break;
            case 2:
                stringstream1 << (u64) vector1[i];
                break;
            case 3:
                stringstream1 << (u128) vector1[i];
                break;
            case 4:
                stringstream1 << (u256) vector1[i];
                break;
            case 5:
                stringstream1 << (d64) vector1[i];
                break;
            case 6:
                stringstream1 << (boolean) vector1[i];
                break;
            case 7:
                stringstream1 << (collection) vector1[i];
                break;
            case 8:
                stringstream1 << (str) vector1[i];
                break;
            default:
                break;
        }
        (i != vector.size() - 1) ? stringstream1 <<  ',' : stringstream1 << ']';
    }

    std::cout << stringstream1.str() << std::endl;


//    std::cout << stringstream.str() << std::endl;
    return 0;
}
