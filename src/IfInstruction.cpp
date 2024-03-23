//
// Created by marci on 2024. 03. 16..
//

#include "../include/IfInstruction.h"

IfInstruction::IfInstruction(int lineNumber, const string& expression) : Instruction(lineNumber, expression) {
    instrTy = InstructionType::If;
}

void IfInstruction::Execute(vector<Register> &registers, vector<Instruction*> &instructions, int &instructionIndex) {

}
IfInstruction::~IfInstruction() {
//    delete[] expression;
}

