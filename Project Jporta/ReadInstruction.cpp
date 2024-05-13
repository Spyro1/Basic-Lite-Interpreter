//
// Created by marci on 2024. 03. 16..
//
#include <iostream>
#include "ReadInstruction.h"
#include "memtrace.h"

ReadInstruction::ReadInstruction(int lineNumber, const string& expression) : Instruction(lineNumber, expression, Read) {}

void ReadInstruction::Execute(std::map<string, float>& registers, vector<Instruction*> &instructions, int &instructionIndex) {
    float newValue;
    string readValue;
    std::getline(std::cin, readValue);

    // Error handling if not empty string
    if (readValue.empty()){
        readValue = "0";
    }
    if (isNumber(readValue))
        newValue = stof(readValue); // Convert value to float
    else
        throw UniqueError("Invalid input were given!"); // Can not convert, throw error
    // Assign inputted value to register
    registers[expression] = newValue;
    // Skip instruction if empty
    instructionIndex++;
}