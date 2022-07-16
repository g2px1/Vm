//
// Created by Kirill Zhukov on 03.07.2022.
//

#ifndef VM_TEST_IMPLEMENTATION_OBJECT_H
#define VM_TEST_IMPLEMENTATION_OBJECT_H
#include "iostream"
#include <boost/json/src.hpp>
#include <utility>
#include "boost/json/object.hpp"


class Object {
public:
    inline Object() { // = default;
        this->object = "NULL_OBJECT";
    }

    inline explicit Object(std::string value, unsigned char type = 0) {
        value.erase(std::remove(value.begin(), value.end(), '\"'), value.end());
        this->object = std::move(value);
        this->type = type;
    }

    inline explicit Object(std::string &value, unsigned char type = 0) {
        value.erase(std::remove(value.begin(), value.end(), '\"'), value.end());
        this->object = value;
        this->type = type;
    }

    std::string object;
    uint16_t type;

    [[nodiscard]] virtual inline std::optional<std::string> get(std::string key) const {
        boost::json::object obj = boost::json::parse(this->object).as_object();
        if(obj.contains(key))
            try {
                return boost::json::value_to<std::string>(obj.at(key));
            } catch (std::exception &e){
                return std::nullopt;
            }
        else
            return std::nullopt;
    }

    inline virtual std::string toString() {
        return object;
    }

    inline virtual bool equals(Object &object1) {
        return this->object == object1.object;
    }

    inline bool operator<(const Object &rhs) const {
        return this->object < rhs.object;
    }

    inline bool operator>(const Object &rhs) const {
        return rhs < *this;
    }

    inline bool operator<=(const Object &rhs) const {
        return this->object <= rhs.object;
    }

    inline bool operator>=(const Object &rhs) const {
        return rhs <= *this;
    }

    inline bool operator==(const Object &rhs) const {
        return this->object == rhs.object;
    }

    inline friend std::ostream &operator<<(std::ostream &os, const Object &obj) {
        return os << R"({"value":)" << R"(")" << obj.object << R"(")" << R"(,"type":)" << 0 << "}";
    }

//
    // implicit conversion
    template<class T>
    inline operator T() const {
        return T(this->object);
    }

    // explicit conversion
    template<class T>
    inline explicit operator Object *() const {
        return new T(this->object);
    }
};


#endif //VM_TEST_IMPLEMENTATION_OBJECT_H