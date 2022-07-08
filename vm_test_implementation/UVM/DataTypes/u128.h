//
// Created by Kirill Zhukov on 07.07.2022.
//

#ifndef VM_TEST_IMPLEMENTATION_U128_H
#define VM_TEST_IMPLEMENTATION_U128_H

#include <utility>
#include <ostream>
#include "Object.h"
#include "boost/multiprecision/cpp_int.hpp"

class u128 : public Object {
public:
    inline u128() = default;

    inline u128(u128 &u) : Object(u) {
        *this = u;
    }

    inline explicit u128(int u) : Object(std::to_string(u)) {
        this->value = u;
    }

    inline explicit u128(uint64_t &u) : Object(std::to_string(u)) {
        this->value = u;
    }

    inline explicit u128(boost::multiprecision::uint128_t u) : Object(u.str()){
        this->value = std::move(u);
    }

    inline explicit u128(const std::string& str) {
        this->value = boost::multiprecision::uint128_t(str);
    }

    boost::multiprecision::uint128_t value;

    [[nodiscard]] inline const boost::multiprecision::uint128_t &getValue() const {
        return value;
    }

    inline void setValue(const boost::multiprecision::uint128_t &val) {
        u128::value = val;
    }

    inline bool operator==(const u128 &rhs) const {
        return this->value == rhs.value;
    }

    inline bool operator!=(const u128 &rhs) const {
        return !(rhs == *this);
    }

    inline bool operator<(const u128 &rhs) const {
        return value < rhs.value;
    }

    inline bool operator>(const u128 &rhs) const {
        return rhs < *this;
    }

    inline bool operator<=(const u128 &rhs) const {
        return !(rhs < *this);
    }

    inline bool operator>=(const u128 &rhs) const {
        return !(*this < rhs);
    }

    inline boost::multiprecision::uint128_t operator+(const u128 &rhs) const {
        return (this->value + rhs.value);
    }

    inline boost::multiprecision::uint128_t operator-(const u128 &rhs) const {
        if (*this < rhs)
            return 0;
        return (this->value - rhs.value);
    }

    inline u128 &operator+=(u128 &c2) {
        this->value += c2.value;
        return *this;
    }

    inline u128 &operator-=(u128 &c2) {
        if (*this < c2) {
            u128 c1 = u128(0);
            return c1;
        }
        this->value -= c2.value;
        return *this;
    }

    // prefix
    inline u128 &operator++() {
        value += 1;
        return *this;
    }

    inline u128 &operator--() {
        value -= 1;
        return *this;
    }

    // postfix
    inline u128 operator++(int) {
        ++(this->value);
        return *this;
    }

    inline u128 operator--(int) {
        --(this->value);
        return *this;
    }

    inline boost::multiprecision::uint128_t operator*(const u128 &rhs) const {
        return (this->value * rhs.value);
    }

    inline boost::multiprecision::uint128_t operator/(const u128 &rhs) const {
        return (this->value / rhs.value);
    }

    inline boost::multiprecision::uint128_t operator%(const u128 &rhs) const {
        return (this->value % rhs.value);
    }

    inline boost::multiprecision::uint128_t operator^(const u128 &rhs) const {
        return (this->value ^ rhs.value);
    }

    inline boost::multiprecision::uint128_t operator&(const u128 &rhs) const {
        return (this->value & rhs.value);
    }

    inline u128 operator<<(const int num) const {
        return u128(value << num);
    }

    inline u128 operator>>(const int num) const {
        return u128(value >> num);
    }

    inline u128 &operator*=(u128 &c2) {
        this->value *= c2.value;
        return *this;
    }

    inline u128 &operator/=(u128 &c2) {
        this->value /= c2.value;
        return *this;
    }

    inline u128 &operator%=(u128 &c2) {
        this->value %= c2.value;
        return *this;
    }

    inline u128 &operator^=(u128 &c2) {
        this->value ^= c2.value;
        return *this;
    }

    inline u128 &operator&=(u128 &c2) {
        this->value &= c2.value;
        return *this;
    }

    inline u128 &operator=(const u128 &c2) {
        this->value = c2.value;
        return *this;
    }

    inline friend std::ostream &operator<<(std::ostream &os, const u128 &u128) {
        os << u128.value;
        return os;
    }

    // implicit conversion
    inline operator Object() const {
        return Object(this->value.str());
    }

    // explicit conversion
    inline operator Object *() const {
        return new Object(this->value.str());
    }
};

#endif //VM_TEST_IMPLEMENTATION_U128_H
