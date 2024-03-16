//
// Created by Szenes Márton on 2024. 03. 14..
//
#include <iostream>
#include <cstring>
#include "PrintInstruction.h"

PrintInstruction::PrintInstruction(int lineNumber, const char *expression) : Instruction(lineNumber, expression) {

}
// -- Virtual function --
void PrintInstruction::Execute(List<Register> &registers, List<Instruction>& instructions, int& instructionIndex) {
    size_t regindex = 0;
    while (strcmp(registers[regindex]->getName(), expression) == 0) { regindex++; }
//     Error handeling if unrecognized variable was in expression
    if (regindex >= registers.Count){
        throw "Error: unrecognized variable!";
    }
    else{
        std::cout << registers[regindex]->getValue() << std::endl;
    }
}
