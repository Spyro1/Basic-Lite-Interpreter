//
// Created by Szenes Márton on 2024. 03. 14..
//
#include <vector>
#include "../../memtrace.h"
#include "../../include/compiler/LetInstruction.h"

LetInstruction::LetInstruction(int lineNumber, const string& expression) : Instruction(lineNumber, expression, Let) {}

void LetInstruction::Execute(vector<Register> &registers, vector<Instruction*> &instructions, int &instructionIndex) {
    //  Remove whitespace
    string shortExpression = RemoveWhiteSpace(expression);
    // Evaluate assingment
    string evaluated = ProcessExpression(shortExpression,registers);
    // Step to next instrcution
    instructionIndex++;
}