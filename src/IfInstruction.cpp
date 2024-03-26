//
// Created by marci on 2024. 03. 16..
//

#include <stdexcept>
#include "../include/IfInstruction.h"

IfInstruction::IfInstruction(int lineNumber, const string& expression) : Instruction(lineNumber, expression) {
    instrTy = InstructionType::If;
}
void IfInstruction::Execute(vector<Register> &registers, vector<Instruction*> &instructions, int &instructionIndex) {
    //  Remove whitespace
    string argument = RemoveWhiteSpace(expression);
    // Process expression as a bollean return value
    string evaluatedArgument = ProcessExpression(argument, registers);
    // Convert "0" or "1" to int
    int argumentValue;
    try {
        argumentValue = stoi(evaluatedArgument);
    } catch (std::exception& e){
        throw std::runtime_error(string("[Syntax error]: Can not recognize \"") + expression + string("\" as a if condition in line: ") + std::to_string(lineNumber));
    }
    // If true (1) then jump to the line after "if". If not true, jump to the second line below.
    if (argumentValue == 0){
        instructionIndex += 2;
    }
    else{
        instructionIndex++;
        bool isgoto = instructions[instructionIndex]->getInstructionType() == Goto;
        instructions[instructionIndex]->Execute(registers, instructions, instructionIndex);
        if(!isgoto) instructionIndex++;
    }
}
IfInstruction::~IfInstruction()  = default;