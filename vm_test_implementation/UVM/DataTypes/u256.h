//
// Created by Kirill Zhukov on 07.07.2022.
//

#ifndef VM_TEST_IMPLEMENTATION_U256_H
#define VM_TEST_IMPLEMENTATION_U256_H

#include "Object.h"
#include "boost/multiprecision/cpp_int.hpp"

class u256 : public Object {
public:
    inline u256() = default;

    inline u256(u256 &u) : Object(u) {
        *this = u;
    }

    inline explicit u256(int u) : Object(std::to_string(u)) {
        this->value = u;
    }

    inline explicit u256(uint64_t &u) : Object(std::to_string(u)) {
        this->value = u;
    }

    inline explicit u256(boost::multiprecision::uint256_t u) {
        this->value = std::move(u);
    }

    inline explicit u256(const std::string& str) {
        this->value = boost::multiprecision::uint256_t(str);
    }

    boost::multiprecision::uint256_t value;

    [[nodiscard]] inline const boost::multiprecision::uint256_t &getValue() const {
        return value;
    }

    inline void setValue(const boost::multiprecision::uint256_t &val) {
        u256::value = val;
    }

    inline bool operator==(const u256 &rhs) const {
        return this->value == rhs.value;
    }

    inline bool operator==(const Object &rhs) const {
        return this->value == ((u256)rhs).value;
    }

    inline bool operator!=(const u256 &rhs) const {
        return !(rhs == *this);
    }

    inline bool operator!=(const Object &rhs) const {
        return !((u256) rhs == *this);
    }

    inline bool operator<(const u256 &rhs) const {
        return value < rhs.value;
    }

    inline bool operator<(const Object &rhs) const {
        return value < ((u256)rhs).value;
    }

    inline bool operator>(const u256 &rhs) const {
        return rhs < *this;
    }

    inline bool operator>(const Object &rhs) const {
        return (u256) rhs < *this;
    }

    inline bool operator<=(const u256 &rhs) const {
        return !(rhs < *this);
    }

    inline bool operator<=(const Object &rhs) const {
        return !((u256) rhs < *this);
    }

    inline bool operator>=(const u256 &rhs) const {
        return !(*this < rhs);
    }

    inline bool operator>=(const Object &rhs) const {
        return !(*this < (u256) rhs);
    }

    inline u256 operator+(const u256 &rhs) const {
        return u256(this->value + rhs.value);
    }

    inline u256 operator+(const Object &rhs) const {
        return u256(this->value + ((u256) rhs).value);
    }

    inline u256 operator-(const u256 &rhs) const {
        if (*this < rhs)
            return u256(0);
        return u256(this->value - rhs.value);
    }

    inline u256 operator-(const Object &rhs) const {
        if (*this < rhs)
            return u256(0);
        return u256(this->value - ((u256) rhs).value);
    }

    inline u256 &operator+=(u256 &c2) {
        this->value += c2.value;
        return *this;
    }

    inline u256 &operator+=(Object &c2) {
        this->value +=  ((u256) c2).value;
        return *this;
    }

    inline u256 &operator-=(u256 &c2) {
        if (*this < c2) {
            u256 c1 = u256(0);
            return c1;
        }
        this->value -= c2.value;
        return *this;
    }

    inline u256 &operator-=(Object &c2) {
        if (*this < ((u256) c2)) {
            u256 c1 = u256(0);
            return c1;
        }
        this->value -= ((u256) c2).value;
        return *this;
    }

    // prefix
    inline u256 &operator++() {
        value += 1;
        return *this;
    }

    inline u256 &operator--() {
        value -= 1;
        return *this;
    }

    // postfix
    inline u256 operator++(int) {
        ++(this->value);
        return *this;
    }

    inline u256 operator--(int) {
        --(this->value);
        return *this;
    }

    inline u256 operator*(const u256 &rhs) const {
        return u256(this->value * rhs.value);
    }

    inline u256 operator*(const Object &rhs) const {
        return u256(this->value * ((u256) rhs).value);
    }

    inline u256 operator/(const u256 &rhs) const {
        return u256(this->value / rhs.value);
    }

    inline u256 operator/(const Object &rhs) const {
        return u256(this->value / ((u256) rhs).value);
    }

    inline u256 operator%(const u256 &rhs) const {
        return u256(this->value % rhs.value);
    }

    inline u256 operator%(const Object &rhs) const {
        return u256(this->value % ((u256) rhs).value);
    }

    inline u256 operator^(const u256 &rhs) const {
        return u256(this->value ^ rhs.value);
    }

    inline u256 operator^(const Object &rhs) const {
        return u256(this->value ^ ((u256) rhs).value);
    }

    inline u256 operator&(const u256 &rhs) const {
        return u256(this->value & rhs.value);
    }

    inline u256 operator&(const Object &rhs) const {
        return u256(this->value & ((u256) rhs).value);
    }

    inline u256 operator<<(const int num) const {
        return u256(value << num);
    }

    inline u256 operator>>(const int num) const {
        return u256(value >> num);
    }

    inline u256 &operator*=(u256 &c2) {
        this->value *= c2.value;
        return *this;
    }

    inline u256 &operator*=(Object &c2) {
        this->value *= ((u256) c2).value;
        return *this;
    }

    inline u256 &operator/=(u256 &c2) {
        this->value /= c2.value;
        return *this;
    }

    inline u256 &operator/=(Object &c2) {
        this->value /= ((u256) c2).value;
        return *this;
    }

    inline u256 &operator%=(u256 &c2) {
        this->value %= c2.value;
        return *this;
    }

    inline u256 &operator%=(Object &c2) {
        this->value %= ((u256) c2).value;
        return *this;
    }

    inline u256 &operator^=(u256 &c2) {
        this->value ^= c2.value;
        return *this;
    }

    inline u256 &operator^=(Object &c2) {
        this->value ^= ((u256) c2).value;
        return *this;
    }

    inline u256 &operator&=(u256 &c2) {
        this->value &= c2.value;
        return *this;
    }

    inline u256 &operator&=(Object &c2) {
        this->value &= ((u256) c2).value;
        return *this;
    }

    inline u256 &operator=(const u256 &c2) {
        this->value = c2.value;
        return *this;
    }

    inline u256 &operator=(Object &c2) {
        this->value = ((u256) c2).value;
        return *this;
    }

    inline friend std::ostream &operator<<(std::ostream &os, const u256 &u256) {
        os << u256.value;
        return os;
    }

    // implicit conversion
    inline operator Object() const {
        return Object(this->value.str());
    }

    // explicit conversion
    inline explicit operator Object *() const {
        return new Object(this->value.str());
    }
};

#endif //VM_TEST_IMPLEMENTATION_U256_H