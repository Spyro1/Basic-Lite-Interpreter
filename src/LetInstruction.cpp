//
// Created by Szenes Márton on 2024. 03. 14..
//

#include "../include/LetInstruction.h"

LetInstruction::LetInstruction(int lineNumber, const char *expression) : Instruction(lineNumber, expression) {

}

void LetInstruction::Execute(List<Register> &registers, List<Instruction> &instructions, int &instructionIndex) {

}

