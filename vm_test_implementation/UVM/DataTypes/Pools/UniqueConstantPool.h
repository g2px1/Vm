//
// Created by Kirill Zhukov on 11.07.2022.
//

#ifndef VM_TEST_IMPLEMENTATION_UNIQUECONSTANTPOOL_H
#define VM_TEST_IMPLEMENTATION_UNIQUECONSTANTPOOL_H
#include "iostream"
#include "boost/unordered_map.hpp"
#include "boost/json.hpp"
#include "boost/json/object.hpp"
#include "boost/json/array.hpp"
#include "vector"

class UniqueConstantPool {
public:
    inline explicit UniqueConstantPool(std::string &str) {
        boost::json::value parser = boost::json::parse(str);
        this->programPool = std::vector<std::vector<unsigned char>>(parser.as_array().size());
        for(int i = 0; i < parser.as_array().size(); i++) {
            this->programPool[i] = {boost::json::value_to<std::vector<unsigned char>>(parser.as_array()[i]).begin(), boost::json::value_to<std::vector<unsigned char>>(parser.as_array()[i]).end()};
        }
    }

    inline std::vector<unsigned char> loadFunction(int index) {
        return this->programPool.at(index);
    }

    inline void pushFunction(std::vector<unsigned char> &vector) {
        this->programPool.emplace_back(vector);
    }

private:
    std::vector<std::vector<unsigned char>> programPool;
};


//    boost::json::value parser = boost::json::parse(str);
//    std::vector<std::vector<int>> vector1(parser.as_array().size());
//    for(int i = 0; i < parser.as_array().size(); i++) {
//        std::cout << *boost::json::value_to<std::vector<int>>(parser.as_array()[i]).begin() << std::endl;
//        vector1[i] = {boost::json::value_to<std::vector<int>>(parser.as_array()[i]).begin(), boost::json::value_to<std::vector<int>>(parser.as_array()[i]).end()};
//    }

#endif //VM_TEST_IMPLEMENTATION_UNIQUECONSTANTPOOL_H
