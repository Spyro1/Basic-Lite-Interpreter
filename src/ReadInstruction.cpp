//
// Created by marci on 2024. 03. 16..
//
#include <iostream>

#include "../include/ReadInstruction.h"

ReadInstruction::ReadInstruction(int lineNumber, const string& expression) : Instruction(lineNumber, expression) {
    instrTy = InstructionType::Read;
}

void ReadInstruction::Execute(vector<Register> &registers, vector<Instruction*> &instructions, int &instructionIndex) {
    using namespace std;
    size_t regIndex = Register::FindRegisterIndex(registers, expression);
    // Error handling if unrecognized variable was in expression
    if (regIndex >= registers.size()) {
        throw std::runtime_error(string("[Syntax error]: Uninitialized register used in line: ") + to_string(lineNumber));
    }
    else{
        float newValue;
        cin >> newValue;
        registers[regIndex].SetValue(newValue);
    }
    instructionIndex++;
}
ReadInstruction::~ReadInstruction()  = default;