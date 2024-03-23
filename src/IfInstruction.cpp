//
// Created by marci on 2024. 03. 16..
//

#include "../include/IfInstruction.h"

IfInstruction::IfInstruction(int lineNumber, const string& expression) : Instruction(lineNumber, expression) {
    instrTy = InstructionType::If;
}

void IfInstruction::Execute(vector<Register> &registers, vector<Instruction*> &instructions, int &instructionIndex) {
    //  Remove whitespace
    string argument = RemoveWhiteSpace(expression);
    // Process expression as a bollean return value
    string evaluatedArgument = ProcessExpression(argument, registers, Boolean);
    // Convert "0" or "1" to int
    int argumentValue = stoi(evaluatedArgument);
    // If true (1) then jump to the line after "if". If not true, jump to the second line below.
    if (argumentValue == 0){
        instructionIndex += 2;
    }
    else{
        instructionIndex++;
        instructions[instructionIndex]->Execute(registers, instructions, instructionIndex);
        instructionIndex++;
    }
}
IfInstruction::~IfInstruction() {
//    delete[] expression;
}

