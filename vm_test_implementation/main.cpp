#include <iostream>
#include "UVM/STRUCTURES/Object.h"

int main() {
    std::string str = R"({"test": "1"})";
    std::string str1 = R"({"test": "2"})";
    Object object = Object(str);
    Object object1 = Object(str1);
    std::cout << object.toString();
    return 0;
}
