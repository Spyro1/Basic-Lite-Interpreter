//
// Created by marci on 2024. 03. 16..
//

#include "../include/ReadInstruction.h"

ReadInstruction::ReadInstruction(int lineNumber, const char *expression) : Instruction(lineNumber, expression) {

}

void ReadInstruction::Execute(List<Register> &registers, List<Instruction> &instructions, int &instructionIndex) {

}
