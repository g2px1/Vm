//
// Created by Kirill Zhukov on 07.07.2022.
//

#ifndef VM_TEST_IMPLEMENTATION_BOOLEAN_H
#define VM_TEST_IMPLEMENTATION_BOOLEAN_H
#include "Object.h"
#include <boost/lexical_cast.hpp>


class boolean : public Object{
public:
    inline boolean() = default;

    inline explicit boolean(bool &value) : Object((value) ? "true" : "false"){
        this->value = value;
    }

    inline explicit boolean(const std::string &str){ // : Object(std::move(str))
        try {
            this->value = boost::lexical_cast<bool>(str);
            std::cout << "ok" << std::endl;
        } catch (boost::bad_lexical_cast::bad_lexical_cast::bad_cast &) {
            this->value = (str == "true");
        }
    }

    inline explicit boolean(int value) : Object((value) ? "true" : "false"){
        this->value = value;
    }

    bool value{};

    inline bool operator==(const boolean &rhs) const {
        return this->value == rhs.value;
    }

    inline bool operator!=(const boolean &rhs) const {
        return !(rhs == *this);
    }

    inline friend std::ostream &operator<<(std::ostream &os, const boolean &boolean1) {
        os << boolean1.value;
        return os;
    }

    // implicit conversion
    inline operator Object() const {
        return Object((this->value) ? "true" : "false");
    }

    // explicit conversion
    inline explicit operator Object *() const {
        return new Object((this->value) ? "true" : "false");
    }
};

#endif //VM_TEST_IMPLEMENTATION_BOOLEAN_H
