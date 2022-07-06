//
// Created by Kirill Zhukov on 02.07.2022.
//

#include "VM.h"

VM::VM(uint16_t contractSize) : contract_size(contractSize) {
    if (contractSize > 25536) throw std::overflow_error("size of contract should be lower then 25536 bytes");
    this->contract_size = contractSize;
}
