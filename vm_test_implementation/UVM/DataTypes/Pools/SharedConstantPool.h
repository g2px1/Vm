//
// Created by Kirill Zhukov on 11.07.2022.
//

#ifndef VM_TEST_IMPLEMENTATION_SHAREDCONSTANTPOOL_H
#define VM_TEST_IMPLEMENTATION_SHAREDCONSTANTPOOL_H
#include "tuple"
#include "vector"
#include "boost/unordered_map.hpp"
#include "../Object.h"

class SharedConstantPool {
public:
    std::vector<void*> references;
};

#endif //VM_TEST_IMPLEMENTATION_SHAREDCONSTANTPOOL_H
