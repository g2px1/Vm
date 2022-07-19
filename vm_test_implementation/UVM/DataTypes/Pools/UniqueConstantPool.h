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
#include "optional"
#include "vector"
#include "../Object.h"
#include "../u128.h"
#include "../boolean.h"
#include "../i32.h"
#include "../u64.h"
#include "../u256.h"
#include "../d64.h"
#include "../str.h"
#include "../collection.h"

class UniqueConstantPool {
public:
    UniqueConstantPool() = default;

    inline explicit UniqueConstantPool(const std::string& str) {
        boost::json::value parsed = boost::json::parse(str);
        this->programPool = parsed.at("functions");
        this->deserialize(parsed.at("values"));
    }

    inline std::optional<boost::json::array> loadFunction(std::string &name) {
        std::tuple exist = this->function_exist(name);
        if (!std::get<0>(exist))
            return std::nullopt;
        return this->programPool.as_array()[std::get<1>(exist)].at(name).as_array();
    }

    inline Object loadReference(int index) {
        return dataValues[index];
    }

    inline void updateReferenceValue(int index, Object &value) {
        this->dataValues[index] = value;
    }

    inline std::string serialize(){
        boost::json::object obj;
        obj.emplace("functions", programPool);
        obj.emplace("values", boost::json::parse(this->serializeValues()));
        return boost::json::serialize(obj);
    }

private:
    boost::json::value programPool;
    std::vector<Object> dataValues;

    inline std::string serializeValues() {
        std::stringstream stringstream;
        stringstream << "[";
        for(int i = 0; i < dataValues.size(); i++) {
            switch (dataValues[i].type) {
                case 1:
                    stringstream << (i32) dataValues[i];
                    break;
                case 2:
                    stringstream << (u64) dataValues[i];
                    break;
                case 3:
                    stringstream << (u128) dataValues[i];
                    break;
                case 4:
                    stringstream << (u256) dataValues[i];
                    break;
                case 5:
                    stringstream << (d64) dataValues[i];
                    break;
                case 6:
                    stringstream << (boolean) dataValues[i];
                    break;
                case 7:
                    stringstream << (collection) dataValues[i];
                    break;
                case 8:
                    stringstream << (str) dataValues[i];
                    break;
                default:
                    stringstream << (Object) dataValues[i];
                    break;
            }
            (i != dataValues.size() - 1) ? stringstream << ',' : stringstream << ']';
        }
        return stringstream.str();
    }

    inline void deserialize(boost::json::value jv) {
        for (int i = 0; i < jv.as_array().size(); i++) {
            switch (jv.as_array()[i].as_object()["type"].as_int64()) {
                case 0:
                    this->dataValues.emplace_back(Object(boost::json::serialize(jv.as_array()[i].at("value"))));
                    break;
                case 1:
                    this->dataValues.emplace_back(i32(boost::json::serialize(jv.as_array()[i].at("value"))));
                    break;
                case 2:
                    this->dataValues.emplace_back(u64(boost::json::serialize(jv.as_array()[i].at("value"))));
                    break;
                case 3:
                    this->dataValues.emplace_back(u128(boost::json::serialize(jv.as_array()[i].at("value"))));
                    break;
                case 4:
                    this->dataValues.emplace_back(u256(boost::json::serialize(jv.as_array()[i].at("value"))));
                    break;
                case 5:
                    this->dataValues.emplace_back(d64(boost::json::serialize(jv.as_array()[i].at("value"))));
                    break;
                case 6:
                    this->dataValues.emplace_back(boolean(boost::json::serialize(jv.as_array()[i].at("value"))));
                    break;
                case 7:
                    this->dataValues.emplace_back(collection(boost::json::serialize(jv.as_array()[i].at("value"))));
                    break;
                case 8:
                    this->dataValues.emplace_back(str(boost::json::serialize(jv.as_array()[i].as_object()["value"])));
                    break;
                default:
                    break;
            }
        }
    }

    std::tuple<bool, int> function_exist(std::string &name) {
        for(int i = 0; i < this->programPool.as_array().size(); i++)
            if (this->programPool.as_array()[i].as_object().contains(name))
                return std::make_tuple(true, i);
        return std::make_tuple(true, -1);
    }
};


//    boost::json::value parser = boost::json::parse(str);
//    std::vector<std::vector<int>> vector1(parser.as_array().size());
//    for(int i = 0; i < parser.as_array().size(); i++) {
//        std::cout << *boost::json::value_to<std::vector<int>>(parser.as_array()[i]).begin() << std::endl;
//        vector1[i] = {boost::json::value_to<std::vector<int>>(parser.as_array()[i]).begin(), boost::json::value_to<std::vector<int>>(parser.as_array()[i]).end()};
//    }

#endif //VM_TEST_IMPLEMENTATION_UNIQUECONSTANTPOOL_H
