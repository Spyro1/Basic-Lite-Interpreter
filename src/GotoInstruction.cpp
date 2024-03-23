//
// Created by marci on 2024. 03. 16..
//

#include "../include/GotoInstruction.h"

GotoInstruction::GotoInstruction(int lineNumber, const string& expression) : Instruction(lineNumber, expression) {
    instrTy = InstructionType::Goto;
}

void GotoInstruction::Execute(vector<Register> &registers, vector<Instruction*>& instructions, int &instructionIndex) {
    int jumpNumber = -1;
    if ((jumpNumber = std::stoi(expression))) {
        int i = 0;
        bool found = false;
        while ((size_t)i < instructions.size() && !found) {
            if (instructions[i]->getLineNumber() == jumpNumber) {
                instructionIndex = i;
                found = true;
            }
            i++;
        }
        if (!found)
            throw std::logic_error(string("Logic error: No line identifier found to jump to in line: ") + std::to_string(lineNumber));
    }
    else
        throw std::runtime_error(string("Can not recognize goto argument in line: ") + std::to_string(lineNumber));
}
GotoInstruction::~GotoInstruction() {
//    delete[] expression;
}