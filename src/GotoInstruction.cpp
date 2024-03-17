//
// Created by marci on 2024. 03. 16..
//

#include "../include/GotoInstruction.h"

GotoInstruction::GotoInstruction(int lineNumber, const char *expression) : Instruction(lineNumber, expression) {

}

void GotoInstruction::Execute(List<Register> &registers, List<Instruction> &instructions, int &instructionIndex) {
    int jumpNumber;
    if ((jumpNumber = std::stoi(expression))){
        int i = 0;
        while ((size_t)i < instructions.Count){
            if (instructions[i]->getLineNumber() == jumpNumber){
                instructionIndex = i;
                break;
            }
            i++;
        }
    }
    else
        throw std::runtime_error("Can not recognize goto argument");
}