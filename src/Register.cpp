//
// Created by Szenes Márton on 2024. 03. 14..
//
#include <cstring>
#include <algorithm>
#include "../include/Register.h"

Register::Register() = default; //: value(0) { }

Register::Register(string name, int defValue) : value(defValue) {
    this->name = name;
}

Register::~Register() = default;

int Register::FindRegisterIndex(const std::vector<Register>& registers, const string& name) {
    // Iterate through the vector array
    auto it = std::find_if(registers.begin(), registers.end(), [&name](const Register& reg) {
        return reg.getName() == name;
    });

    if (it != registers.end()) {
        return (int)std::distance(registers.begin(), it); // Return the index of register in array if found
    } else {
        return -1; // Return -1 to indicate register name is not found
    }
}
