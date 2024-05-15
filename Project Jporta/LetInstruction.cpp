//
// Created by Szenes Márton on 2024. 03. 14..
//
#include <vector>
#include "LetInstruction.h"
#include "memtrace.h"

LetInstruction::LetInstruction(int lineNumber, const string& expression) : Instruction(lineNumber, expression, Let) {}

void LetInstruction::Execute(std::map<string, float>& registers, vector<Instruction*> &instructions, int &instructionIndex) {
    //  Remove whitespace
    string shortExpression = RemoveWhiteSpace(expression);
    // Evaluate assignment
    string evaluated = ProcessExpression(shortExpression,registers);
    // Step to next instruction
    instructionIndex++;
}