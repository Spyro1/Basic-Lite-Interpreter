//
// Created by Szenes Márton on 2024. 03. 14..
//
#include <cstring>
#include "../include/Instruction.h"

Instruction::Instruction() : lineNumber(0) { }

Instruction::Instruction(int lineNumber, const char *expression) : lineNumber(lineNumber) {
    this->expression = new char[strlen(expression) + 1];
    strcpy(this->expression, expression);
}

int Instruction::getLineNumber() const {
    return lineNumber;
}

Instruction::~Instruction() {
    delete[] expression;
}


