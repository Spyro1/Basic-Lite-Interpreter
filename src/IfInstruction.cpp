//
// Created by marci on 2024. 03. 16..
//

#include "../include/IfInstruction.h"

IfInstruction::IfInstruction(int lineNumber, const char *expression) : Instruction(lineNumber, expression) {

}

void IfInstruction::Execute(List<Register> &registers, List<Instruction> &instructions, int &instructionIndex) {

}

