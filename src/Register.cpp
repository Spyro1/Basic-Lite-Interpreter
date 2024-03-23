//
// Created by Szenes Márton on 2024. 03. 14..
//
#include <cstring>
#include "../include/Register.h"

Register::Register() = default; //: value(0) { }

Register::Register(string name, int defValue) : value(defValue) {
    this->name = name;
}

Register::~Register() {
//    delete[] name;
}
