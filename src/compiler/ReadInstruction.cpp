//
// Created by marci on 2024. 03. 16..
//
#include <iostream>

#include "../../include/compiler/ReadInstruction.h"

ReadInstruction::ReadInstruction(int lineNumber, const string& expression) : Instruction(lineNumber, expression, Read) {}

void ReadInstruction::Execute(vector<Register> &registers, vector<Instruction*> &instructions, int &instructionIndex) {
    float newValue;
    string readValue;
    size_t regIndex = FindRegisterIndex(registers, expression);
#ifdef CPORTA
    std::getline(inStream, readValue);
#else
    std::getline(std::cin, readValue);
#endif

    // Error handling
    if (!readValue.empty()){
        if (isNumber(readValue))
            newValue = stof(readValue);
        else
            throw UniqueError("Incorrect input were given!");

        if (Exists(regIndex))
            registers[regIndex].SetValue(newValue); // Assign value to existing register
        else
            registers.emplace_back(expression, newValue); // Create new register and initialize it
    }

    instructionIndex++;
}