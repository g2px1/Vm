//
// Created by Kirill Zhukov on 07.07.2022.
//

#ifndef VM_TEST_IMPLEMENTATION_COLLECTION_H
#define VM_TEST_IMPLEMENTATION_COLLECTION_H
#include "Object.h"
#include "vector"

class collection : public Object{
public:
    collection() = default;
    std::vector<Object> value;

    inline void emplace_back(const Object& obj) {
        value.emplace_back(obj);
    }

    inline void push_back(const Object& obj) {
        value.push_back(obj);
    }

    inline void pop_back() {
        return value.pop_back();
    }

    template<class T>
    inline T forEach(std::function<T> func) {
        func(this->value);
    }

    template<class T>
    inline T getWithCast(int index){
        return (T) this->value[index];
    }

    inline Object& operator[](int index) {
        return this->value[index];
    }
};
#endif //VM_TEST_IMPLEMENTATION_COLLECTION_H