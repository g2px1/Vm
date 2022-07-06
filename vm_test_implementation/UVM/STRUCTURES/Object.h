////
//// Created by Kirill Zhukov on 03.07.2022.
////
//
#ifndef VM_TEST_IMPLEMENTATION_OBJECT_H
#define VM_TEST_IMPLEMENTATION_OBJECT_H
#include "iostream"

#include <boost/json/src.hpp>
#include <utility>
#include "boost/json/object.hpp"

class Object {
public:
    Object() = default;

    inline explicit Object(std::string &value) {
        this->object = boost::json::parse(value).as_object();
    }

    inline explicit Object(boost::json::object object) {
        this->object = std::move(object);
    }

    boost::json::object object;

    [[nodiscard]] inline std::optional<std::string> get(std::string key) const {
        if(object.contains(key))
        return boost::json::value_to<std::string>(this->object.at(key));
        else
            return std::nullopt;
    }

    virtual inline std::string toString() {
        return boost::json::serialize(this->object);
    }

    virtual inline bool equals(Object &object1) {
        return this->object == object1.object;
    }
};


#endif //VM_TEST_IMPLEMENTATION_OBJECT_H


//    std::string js = R"({
//    "table":"orderBookL2_25",
//    "action":"insert",
//    "data":[
//        {
//            "symbol":"XBTUSD",
//            "id":8796514950,
//            "side":"Buy",
//            "size":10000,
//            "price":34850.5
//        },
//        {
//            "symbol":"XBTUSD",
//            "id":8796515700,
//            "side":"Buy",
//            "size":281,
//            "price":34843
//        }
//    ]
//    })";
//
//    boost::json::parse_options opt;                     // all extensions default to off
//    opt.allow_comments = true;                          // permit C and C++ style comments to appear in whitespace
//    opt.allow_trailing_commas = true;                   // allow an additional trailing comma in object and array element lists
//    opt.allow_invalid_utf8 = true;                      // skip utf-8 validation of keys and strings
//    boost::json::object object = boost::json::parse(js, boost::json::storage_ptr(), opt).as_object();
//
//    boost::json::object obj2( boost::json::make_shared_resource<boost::json::monotonic_resource>() ); // empty object, uses a counted monotonic resource

//    std::vector<std::variant<int, std::string, float>> var = {10, "esre", 10.0};
//    std::array<std::pair<std::string, int>, 3> test{{"awda", 1}, {"b", 2}, {"c", 3}};