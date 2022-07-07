//
// Created by Kirill Zhukov on 07.07.2022.
//

#ifndef VM_TEST_IMPLEMENTATION_U64_H
#define VM_TEST_IMPLEMENTATION_U64_H
#include "Object.h"

class u64 : public Object {
public:
    inline u64() = default;

    inline u64(u64 &u) : Object(u) {
        *this = u;
    }

    inline explicit u64(int u) : Object(std::to_string(u)) {
        this->value = u;
    }

    inline explicit u64(uint64_t &u) : Object(std::to_string(u)) {
        this->value = u;
    }

    inline explicit u64(uint64_t u) {
        this->value = u;
    }

    uint64_t value{};

    [[nodiscard]] inline const uint64_t &getValue() const {
        return value;
    }

    inline void setValue(const uint64_t &val) {
        u64::value = val;
    }

    inline bool operator==(const u64 &rhs) const {
        return this->value == rhs.value;
    }

    inline bool operator!=(const u64 &rhs) const {
        return !(rhs == *this);
    }

    inline bool operator<(const u64 &rhs) const {
        return value < rhs.value;
    }

    inline bool operator>(const u64 &rhs) const {
        return rhs < *this;
    }

    inline bool operator<=(const u64 &rhs) const {
        return !(rhs < *this);
    }

    inline bool operator>=(const u64 &rhs) const {
        return !(*this < rhs);
    }

    inline uint64_t operator+(const u64 &rhs) const {
        return (this->value + rhs.value);
    }

    inline uint64_t operator-(const u64 &rhs) const {
        if (*this < rhs)
            return 0;
        return (this->value - rhs.value);
    }

    inline u64 &operator+=(u64 &c2) {
        this->value += c2.value;
        return *this;
    }

    inline u64 &operator-=(u64 &c2) {
        if (*this < c2) {
            u64 c1 = u64(0);
            return c1;
        }
        this->value -= c2.value;
        return *this;
    }

    // prefix
    inline u64 &operator++() {
        value += 1;
        return *this;
    }

    inline u64 &operator--() {
        value -= 1;
        return *this;
    }

    // postfix
    inline u64 operator++(int) {
        ++(this->value);
        return *this;
    }

    inline u64 operator--(int) {
        --(this->value);
        return *this;
    }

    inline uint64_t operator*(const u64 &rhs) const {
        return (this->value * rhs.value);
    }

    inline uint64_t operator/(const u64 &rhs) const {
        return (this->value / rhs.value);
    }

    inline uint64_t operator%(const u64 &rhs) const {
        return (this->value % rhs.value);
    }

    inline uint64_t operator^(const u64 &rhs) const {
        return (this->value ^ rhs.value);
    }

    inline uint64_t operator&(const u64 &rhs) const {
        return (this->value & rhs.value);
    }

    inline u64 operator<<(const int num) const {
        return u64(value << num);
    }

    inline u64 operator>>(const int num) const {
        return u64(value >> num);
    }

    inline u64 &operator*=(u64 &c2) {
        this->value *= c2.value;
        return *this;
    }

    inline u64 &operator/=(u64 &c2) {
        this->value /= c2.value;
        return *this;
    }

    inline u64 &operator%=(u64 &c2) {
        this->value %= c2.value;
        return *this;
    }

    inline u64 &operator^=(u64 &c2) {
        this->value ^= c2.value;
        return *this;
    }

    inline u64 &operator&=(u64 &c2) {
        this->value &= c2.value;
        return *this;
    }

    inline u64 &operator=(const u64 &c2) {
        this->value = c2.value;
        return *this;
    }

    inline friend std::ostream &operator<<(std::ostream &os, const u64 &u64) {
        os << u64.value;
        return os;
    }

    // implicit conversion
    inline operator Object() const {
        return Object(std::to_string(this->value));
    }

    // explicit conversion
    inline explicit operator Object *() const {
        return new Object(std::to_string(this->value));
    }
};
#endif //VM_TEST_IMPLEMENTATION_U64_H
