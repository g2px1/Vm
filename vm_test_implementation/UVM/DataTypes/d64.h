//
// Created by Kirill Zhukov on 07.07.2022.
//

#ifndef VM_TEST_IMPLEMENTATION_D64_H
#define VM_TEST_IMPLEMENTATION_D64_H
#include "Object.h"
#include "cmath"

class d64 : public Object {
public:
    inline d64() = default;

    inline d64(d64 &u) : Object(u) {
        *this = u;
    }

    inline explicit d64(double u) : Object(std::to_string(u)) {
        this->value = u;
    }

    inline explicit d64(const std::string &str) {
        this->value = std::stod(str);
    }

    double value{};

    [[nodiscard]] inline const double &getValue() const {
        return value;
    }

    inline void setValue(const double &val) {
        d64::value = val;
    }

    inline bool operator==(const d64 &rhs) const {
        return this->value == rhs.value;
    }

    inline bool operator!=(const d64 &rhs) const {
        return !(rhs == *this);
    }

    inline bool operator<(const d64 &rhs) const {
        return value < rhs.value;
    }

    inline bool operator>(const d64 &rhs) const {
        return rhs < *this;
    }

    inline bool operator<=(const d64 &rhs) const {
        return !(rhs < *this);
    }

    inline bool operator>=(const d64 &rhs) const {
        return !(*this < rhs);
    }

    inline double operator+(const d64 &rhs) const {
        return (this->value + rhs.value);
    }

    inline double operator-(const d64 &rhs) const {
        if (*this < rhs)
            return 0;
        return (this->value - rhs.value);
    }

    inline d64 &operator+=(d64 &c2) {
        this->value += c2.value;
        return *this;
    }

    inline d64 &operator-=(d64 &c2) {
        if (*this < c2) {
            d64 c1 = d64(0);
            return c1;
        }
        this->value -= c2.value;
        return *this;
    }

    // prefix
    inline d64 &operator++() {
        value += 1;
        return *this;
    }

    inline d64 &operator--() {
        value -= 1;
        return *this;
    }

    // postfix
    inline d64 operator++(int) {
        ++(this->value);
        return *this;
    }

    inline d64 operator--(int) {
        --(this->value);
        return *this;
    }

    inline double operator*(const d64 &rhs) const {
        return (this->value * rhs.value);
    }

    inline double operator/(const d64 &rhs) const {
        return (this->value / rhs.value);
    }

    inline double operator%(const d64 &rhs) const {
        return (fmod(this->value, rhs.value));
    }

    inline d64 &operator*=(d64 &c2) {
        this->value *= c2.value;
        return *this;
    }

    inline d64 &operator/=(d64 &c2) {
        this->value /= c2.value;
        return *this;
    }

    inline d64 &operator=(const d64 &c2) {
        this->value = c2.value;
        return *this;
    }

    inline d64 &operator=(const double &c2) {
        this->value = c2;
        return *this;
    }

    inline friend std::ostream &operator<<(std::ostream &os, const d64 &d64) {
        os << d64.value;
        return os;
    }

    // implicit conversion
    inline explicit operator Object() const {
        return Object(std::to_string(this->value));
    }

    // explicit conversion
    inline explicit operator Object *() const {
        return new Object(std::to_string(this->value));
    }

    inline virtual std::string toString() override {
        return std::to_string(this->value);
    }
};
#endif //VM_TEST_IMPLEMENTATION_D64_H
