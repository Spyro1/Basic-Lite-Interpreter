//
// Created by marci on 2024. 03. 16..
//

#include <stdexcept>
#include "IfInstruction.h"
#include "memtrace.h"

IfInstruction::IfInstruction(int lineNumber, const string& expression) : Instruction(lineNumber, expression, If) {}

void IfInstruction::Execute(vector<Register> &registers, vector<Instruction*> &instructions, int &instructionIndex) {
    //  Remove whitespace
    string argument = RemoveWhiteSpace(expression);
    // Process expression as a boolean return value
    string evaluatedArgument = ProcessExpression(argument, registers);
    // Convert "0" or "1" to int
    int argumentValue;
    try {
        argumentValue = stoi(evaluatedArgument);
    } catch (std::exception& e){
        throw SyntaxError("Can not recognize \"" + expression + "\" as an if condition", lineNumber);
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