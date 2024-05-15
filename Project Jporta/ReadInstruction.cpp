//
// Created by marci on 2024. 03. 16..
//
#include <iostream>
#include "ReadInstruction.h"
#include "memtrace.h"

ReadInstruction::ReadInstruction(int lineNumber, const string& expression) : Instruction(lineNumber, expression, Read) {}

void ReadInstruction::Execute(std::map<string, float>& registers, vector<Instruction*> &instructions, int &instructionIndex) {
    // Get line from user
    string readValue;
    std::getline(std::cin, readValue);

    string shortExpression = RemoveWhiteSpace(readValue); //  Remove whitespace
    string assignment = expression + "=" + shortExpression; // Gluing the given expression with the given value: Example: 10 read a --> a = <input>
    try{
        string evaluated = ProcessExpression(assignment, registers); // Process the expression
    } catch (std::exception& e){
        // Error handling if the inputted string contained a wrong formula
        throw UniqueError(string("Invalid input were given!\n") + e.what()); // Can not convert, throw error
    }
    // Go to next instruction
    instructionIndex++;
}