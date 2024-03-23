//
// Created by marci on 2024. 03. 16..
//

#include "../include/ReadInstruction.h"

ReadInstruction::ReadInstruction(int lineNumber, const string& expression) : Instruction(lineNumber, expression) {
    instrTy = InstructionType::Read;
}

void ReadInstruction::Execute(vector<Register> &registers, vector<Instruction*> &instructions, int &instructionIndex) {

}
ReadInstruction::~ReadInstruction() {
//    delete[] expression;
}
