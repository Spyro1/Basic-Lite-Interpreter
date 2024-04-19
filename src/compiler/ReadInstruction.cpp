//
// Created by marci on 2024. 03. 16..
//
#include <iostream>

#include "../../include/compiler/ReadInstruction.h"

ReadInstruction::ReadInstruction(int lineNumber, const string& expression) : Instruction(lineNumber, expression, Read) {}

void ReadInstruction::Execute(vector<Register> &registers, vector<Instruction*> &instructions, int &instructionIndex) {
    size_t regIndex = FindRegisterIndex(registers, expression);
    // Error handling if unrecognized variable was in expression
    if (regIndex >= registers.size()) {
        throw SyntaxError("Uninitialized register used", lineNumber);
    }
    else{
        float newValue;
        std::cin >> newValue;
        registers[regIndex].SetValue(newValue);
    }
    instructionIndex++;
}