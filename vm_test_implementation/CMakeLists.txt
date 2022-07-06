cmake_minimum_required(VERSION 3.21)
project(vm_test_implementation)

set(CMAKE_CXX_STANDARD 17)
find_package(Boost)

SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++17")

add_executable(vm_test_implementation main.cpp UVM/VM.cpp UVM/VM.h UVM/OPCODES/Opcodes.h UVM/STRUCTURES/Object.h)
target_link_libraries(${PROJECT_NAME} Boost::boost)