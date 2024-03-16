//
// Created by marci on 2024. 03. 16..
//

#include "../include/GotoInstruction.h"

GotoInstruction::GotoInstruction(int lineNumber, const char *expression) : Instruction(lineNumber, expression) {

}

void GotoInstruction::Execute(List<Register> &registers, List<Instruction> &instructions, int &instructionIndex) {

}