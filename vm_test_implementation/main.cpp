#include <iostream>
#include "vector"
#include "map"
#include <boost/json/src.hpp>
#include <boost/json/value.hpp>
#include "boost/json/value_from.hpp"
#include "boost/unordered_map.hpp"
#include "string"

int main() {
    std::vector< int > v1{ 1, 2, 3, 4 };
    std::map<std::string, std::vector<int>> map = {{"test", v1}};
    boost::unordered_map<std::string, std::vector<int>> unorderedMap = {{"test1", v1}};
// Convert the vector to a JSON array
    boost::json::value jv = boost::json::value_from( unorderedMap );
    boost::unordered_map<std::string, std::vector<int>> unorderedMap1 = boost::json::value_to<boost::unordered_map<std::string, std::vector<int>>>(jv);
//            value_to<boost::unordered_map<std::string, std::vector<int>>>();
    boost::json::value val1 = boost::json::value_from(unorderedMap1).at("test1");

    std::vector<int> vector(boost::json::value_to<std::vector<int>>(val1).begin(), boost::json::value_to<std::vector<int>>(val1).end());
//            (val1.at("test1").as_array().begin(), val1.at("test1").as_array().end());

    std::string str = boost::json::serialize(jv);

    std::cout << jv << std::endl << str; // << str
    return 0;
}
