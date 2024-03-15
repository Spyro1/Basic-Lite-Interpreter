//
// Created by Szenes Márton on 2024. 03. 14..
//
#include <cstring>
#include "Register.h"

Register::Register() = default; //: value(0) { }

Register::Register(const char *name, int defValue) : value(defValue) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

const char *Register::getName() const {
    return name;
}

int Register::getValue() const {
    return value;
}

Register::~Register() {
    delete[] name;
}
