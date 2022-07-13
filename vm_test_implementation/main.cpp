#include <iostream>
#include "vector"
#include "map"
#include <boost/json/src.hpp>
#include <boost/json/value.hpp>
#include "boost/json/value_from.hpp"
#include "boost/unordered_map.hpp"
#include "string"
#include "UVM/DataTypes/Object.h"
#include "UVM/DataTypes/u128.h"
#include "UVM/DataTypes/boolean.h"

int main() {
    Object object = Object();
    object.object = "testes";
    u128 u1 = u128(111);
    boolean boolean1 = boolean("true");
    std::vector<Object> vector;
    vector.emplace_back(object);
    vector.emplace_back(u1);
    vector.emplace_back(boolean1);

    boost::json::value jv = boost::json::value_from(vector);

    std::cout << jv;
    return 0;
}
