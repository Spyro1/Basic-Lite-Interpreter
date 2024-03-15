//
// Created by Szenes Márton on 2024. 03. 14..
//
#include <iostream>
#include <cstring>
#include "PrintInstruction.h"
#include "Computer.h"

PrintInstruction::PrintInstruction(int lineNumber, const char *expression) : Instruction(lineNumber, expression) {

}

void PrintInstruction::Execute(Register *registers, size_t registerCount, Instruction *instructions, int &instructionIndex) {
    size_t regindex = 0;
    while (strcmp(registers[regindex].getName(), expression) == 0) { regindex++; }
    // Error handeling if unrecognized variable was in expression
    if (regindex >= registerCount){
        throw std::string("Compile error: unrecognized variable!");// + std::string(lineNumber);
    }
}
