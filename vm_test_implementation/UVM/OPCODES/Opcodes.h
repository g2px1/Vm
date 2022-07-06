//
// Created by Kirill Zhukov on 02.07.2022.
//

#ifndef VM_TEST_IMPLEMENTATION_OPCODES_H
#define VM_TEST_IMPLEMENTATION_OPCODES_H

enum OPCODES : unsigned char {
    stop = 0x00,
    loop = 0x01,
    swap = 0x02,
    inc = 0x03,
    sub = 0x04,
    divide = 0x05,
    mul = 0x06,
    i_div = 0x07,
    i_xor = 0x08,
    inv = 0x09,
    l_shift = 0xA,
    r_shift = 0xB,
    pop = 0xC,
    push = 0xD,
    dup = 0xE,
    i_or = 0xF,
    i_and = 0x10,
    i_return = 0x11,
    i_sha3 = 0x12,
    i_balance = 0x13,
    i_timestamp = 0x14,
    i_blockhash = 0x15,
    i_chainid = 0x16,
    i_memory_store = 0x17,
    i_memory_value = 0x18,
    i_storage_store = 0x19,
    create = 0x1A,
    destruct = 0x1B,
    jump = 0x1C, // 28
    equal = 0x1D, // 29
    gt = 0x1E, // 30, a > b
    lt = 0x1F, // 31 a < b
    egt = 0x20, // 32 a >= b
    elt = 0x21, // 33 a <= b
    address = 0x22, // 34
    invalid = 0x23 // 35
};
#endif //VM_TEST_IMPLEMENTATION_OPCODES_H
