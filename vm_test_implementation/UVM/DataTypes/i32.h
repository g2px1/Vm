//
// Created by Kirill Zhukov on 07.07.2022.
//

#ifndef VM_TEST_IMPLEMENTATION_I32_H
#define VM_TEST_IMPLEMENTATION_I32_H
#include "Object.h"

class i32 : public Object {
public:
    inline i32() = default;

    inline i32(i32 &u) : Object(u) {
        *this = u;
    }

    inline explicit i32(int u) : Object(std::to_string(u)) {
        this->value = u;
    }

    inline explicit i32(const std::string &str) {
        std::istringstream iss(str);
        iss >> this->value;
    }

    int value{};

    [[nodiscard]] inline const int &getValue() const {
        return value;
    }

    inline void setValue(const int &val) {
        i32::value = val;
    }

    inline bool operator==(const i32 &rhs) const {
        return this->value == rhs.value;
    }

    inline bool operator!=(const i32 &rhs) const {
        return !(rhs == *this);
    }

    inline bool operator<(const i32 &rhs) const {
        return value < rhs.value;
    }

    inline bool operator>(const i32 &rhs) const {
        return rhs < *this;
    }

    inline bool operator<=(const i32 &rhs) const {
        return !(rhs < *this);
    }

    inline bool operator>=(const i32 &rhs) const {
        return !(*this < rhs);
    }

    inline int operator+(const i32 &rhs) const {
        return (this->value + rhs.value);
    }

    inline int operator-(const i32 &rhs) const {
        if (*this < rhs)
            return 0;
        return (this->value - rhs.value);
    }

    inline i32 &operator+=(i32 &c2) {
        this->value += c2.value;
        return *this;
    }

    inline i32 &operator-=(i32 &c2) {
        if (*this < c2) {
            i32 c1 = i32(0);
            return c1;
        }
        this->value -= c2.value;
        return *this;
    }

    // prefix
    inline i32 &operator++() {
        value += 1;
        return *this;
    }

    i32 &operator--() {
        value -= 1;
        return *this;
    }

    // postfix
    inline i32 operator++(int) {
        ++(this->value);
        return *this;
    }

    inline i32 operator--(int) {
        --(this->value);
        return *this;
    }

    inline int operator*(const i32 &rhs) const {
        return (this->value * rhs.value);
    }

    inline int operator/(const i32 &rhs) const {
        return (this->value / rhs.value);
    }

    inline int operator%(const i32 &rhs) const {
        return (this->value % rhs.value);
    }

    inline int operator^(const i32 &rhs) const {
        return (this->value ^ rhs.value);
    }

    inline int operator&(const i32 &rhs) const {
        return (this->value & rhs.value);
    }

    inline i32 operator<<(const int num) const {
        return i32(value << num);
    }

    inline i32 operator>>(const int num) const {
        return i32(value >> num);
    }

    inline i32 &operator*=(i32 &c2) {
        this->value *= c2.value;
        return *this;
    }

    inline i32 &operator/=(i32 &c2) {
        this->value /= c2.value;
        return *this;
    }

    inline i32 &operator%=(i32 &c2) {
        this->value %= c2.value;
        return *this;
    }

    inline i32 &operator^=(i32 &c2) {
        this->value ^= c2.value;
        return *this;
    }

    inline i32 &operator&=(i32 &c2) {
        this->value &= c2.value;
        return *this;
    }

    inline i32 &operator=(const i32 &c2) {
        this->value = c2.value;
        return *this;
    }

    inline friend std::ostream &operator<<(std::ostream &os, const i32 &i32) {
        os << i32.value;
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
};
#endif //VM_TEST_IMPLEMENTATION_I32_H
