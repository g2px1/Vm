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
#include "boost/json/value_from.hpp"
#include "boost/json/value_to.hpp"
#include <boost/json/src.hpp>
#include "vector"
#include "../Object.h"

class UniqueConstantPool {
public:
//    inline explicit UniqueConstantPool(std::string &str) {
//        boost::json::value parser = boost::json::parse(str);
//        this->programPool = std::vector<std::vector<unsigned char>>(parser.as_array().size());
//        for(int i = 0; i < parser.as_array().size(); i++) {
//            this->programPool[i] = {boost::json::value_to<std::vector<unsigned char>>(parser.as_array()[i]).begin(), boost::json::value_to<std::vector<unsigned char>>(parser.as_array()[i]).end()};
//        }
//    }

    inline explicit UniqueConstantPool(std::string &str) {
        this->programPool = boost::json::value_to<boost::unordered_map<std::string, std::vector<unsigned char>>>(boost::json::parse(str));
    }

    inline std::vector<unsigned char> loadFunction(std::string &name) {
        return this->programPool[name];
    }

    inline void pushFunction(std::string &str, std::vector<unsigned char> &vector) {
        this->programPool[str] = vector;
    }

    inline std::string serialize(){
        boost::json::object obj = boost::json::value_from(programPool).as_object();
        obj["values"] = boost::json::value_from(this->programStack).as_object();
        obj["functions"] = boost::json::value_from(this->programPool).as_object();
        return boost::json::serialize(obj);
    }

private:
    boost::unordered_map<std::string, std::vector<unsigned char>> programPool;
    std::vector<Object> programStack;
};


//    boost::json::value parser = boost::json::parse(str);
//    std::vector<std::vector<int>> vector1(parser.as_array().size());
//    for(int i = 0; i < parser.as_array().size(); i++) {
//        std::cout << *boost::json::value_to<std::vector<int>>(parser.as_array()[i]).begin() << std::endl;
//        vector1[i] = {boost::json::value_to<std::vector<int>>(parser.as_array()[i]).begin(), boost::json::value_to<std::vector<int>>(parser.as_array()[i]).end()};
//    }

#endif //VM_TEST_IMPLEMENTATION_UNIQUECONSTANTPOOL_H
