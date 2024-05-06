//
// Created by marci on 2024. 03. 16..
//
#include <iostream>
#include "../../memtrace.h"
#include "../../include/compiler/Expression.h"
#include "../../include/compiler/ReadInstruction.h"

ReadInstruction::ReadInstruction(int lineNumber, const string& expression) : Instruction(lineNumber, expression, Read) {}

void ReadInstruction::Execute(vector<Register> &registers, vector<Instruction*> &instructions, int &instructionIndex) {
    float newValue;
    string readValue;
    size_t regIndex = Expression::FindRegisterIndex(registers, expression);
    std::getline(std::cin, readValue);
//    std::cin >> readValue;

    // Error handling if not empty string
    if (!readValue.empty()){
        if (Expression::isNumber(readValue))
            newValue = stof(readValue); // Convert value to float
        else
            throw UniqueError("Invalid input were given!"); // Can not convert, throw error
        // Assign inputted value to register
        if (regIndex != nopos)
            registers[regIndex].SetValue(newValue); // Assign value to existing register
        else
            registers.emplace_back(expression, newValue); // Create new register and initialize it
    }
    // Skip instruction if empty
    instructionIndex++;
}