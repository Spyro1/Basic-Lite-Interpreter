//
// Created by Szenes Márton on 2024. 03. 14..
//


#include <vector>
#include "../include/LetInstruction.h"


LetInstruction::LetInstruction(int lineNumber, const string& expression) : Instruction(lineNumber, expression) {
    instrTy = InstructionType::Let;
}

void LetInstruction::Execute(vector<Register> &registers, vector<Instruction*> &instructions, int &instructionIndex) {
    //  Remove whitespace
    string shortExpression = RemoveWhiteSpace(expression);
    string evaluated = ProcessExpression(shortExpression,registers,Integer);
    // a = 12       // INT literal
    // a = a + 1    // ADD
    // a = a - 1    // SUB
    // a = a * 1    // MULTIPLY
    // a = a / 1    // DEVIDE
    // a = (3 + a) * a  // BRACKETS
    instructionIndex++;
}

LetInstruction::~LetInstruction() = default;


// -- Private helper functions --
