//
// Created by marci on 2024. 03. 16..
//
#include <iostream>

#include "../../include/compiler/ReadInstruction.h"

ReadInstruction::ReadInstruction(int lineNumber, const string& expression) : Instruction(lineNumber, expression) {
    instrTy = InstructionType::Read;
}

void ReadInstruction::Execute(vector<Register> &registers, vector<Instruction*> &instructions, int &instructionIndex) {
    size_t regIndex = FindRegisterIndex(registers, expression);
    // Error handling if unrecognized variable was in expression
    if (regIndex >= registers.size()) {
        throw std::runtime_error(string("[Syntax error]: Uninitialized register used in line: ") + std::to_string(lineNumber));
    }
    else{
        float newValue;
        std::cin >> newValue;
        registers[regIndex].SetValue(newValue);
    }
    instructionIndex++;
}
ReadInstruction::~ReadInstruction()  = default;