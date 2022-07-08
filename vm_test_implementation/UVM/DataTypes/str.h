//
// Created by Kirill Zhukov on 07.07.2022.
//

#ifndef VM_TEST_IMPLEMENTATION_STR_H
#define VM_TEST_IMPLEMENTATION_STR_H

#include <utility>
#include "Object.h"

class str : public Object {
public:
    inline str() = default;

    inline explicit str(std::string value) { //: Object(std::move(value))
        this->value = std::move(value);
    }

    std::string value{};

    inline char charAt(int num) {
        return this->value.at(num);
    }

    [[maybe_unused]] [[nodiscard]] inline bool compareTo(std::string val) const {
        return this->value == val;
    }

    [[maybe_unused]] inline bool compareTo(str &val) const {
        return *this == val;
    }

    inline str concat(std::string val) {
        return str(this->value + val);
    }

    [[nodiscard]] inline str concat(str val) const {
        return str(*this + val);
    }

    [[nodiscard]] inline bool isEmpty() const {
        return this->value.empty();
    }

    inline void remove(std::string val) {
        std::string::size_type i = this->value.find(val);
        if (i != std::string::npos)
            value.erase(i, val.length());
    }

    inline void remove(str val) {
        *this -= val;
    }

    inline size_t length() {
        return this->value.length();
    }

    inline friend std::ostream &operator<<(std::ostream &os, const str &str1) {
        os << str1.value;
        return os;
    }

    // implicit conversion
    inline operator Object() const {
        return Object(this->value);
    }

    // explicit conversion
    inline explicit operator Object *() const {
        return new Object(this->value);
    }

    inline str &operator=(std::string &rhs) {
        this->value = rhs;
        return *this;
    }

private:
    inline std::string operator+(const str &rhs) const {
        return (this->value + rhs.value);
    }

    inline std::string operator-(const str &rhs) {
        std::string::size_type i = this->value.find(rhs.value);
        if (i != std::string::npos)
            value.erase(i, rhs.value.length());

        return this->value;
    }

    inline str &operator+=(str &c2) {
        this->value += c2.value;
        return *this;
    }

    inline str &operator-=(str &c2) {
        *this - c2;
        return *this;
    }

    bool operator==(const str &rhs) const {
        return this->value == rhs.value;
    }

    bool operator!=(const str &rhs) const {
        return !(rhs == *this);
    }

};

#endif //VM_TEST_IMPLEMENTATION_STR_H
