//
// Created by Szenes Márton on 2024. 03. 14..
//
#include <cstring>
#include "../include/Instruction.h"

Instruction::Instruction() : lineNumber(0) { instrTy = InstructionType::NoType; }

Instruction::Instruction(int lineNumber_, const string &expression_) {
    this->expression = expression_;
    this->lineNumber = lineNumber_;
    instrTy = InstructionType::NoType;
}
int Instruction::getLineNumber() const {
    return lineNumber;
}
string Instruction::getType() const {
    switch (instrTy) {
        case Let: return "let";
        case Print: return "print";
        case Goto: return "goto";
        case If: return "if";
        case Read: return "read";
        default: return "unknown";
    }
}
string Instruction::getExpression() const {
    return expression;
}

std::ostream& operator<<(std::ostream &os, const Instruction& inst) {
    os << inst.getLineNumber() << " " << inst.getType() << " " << inst.getExpression();
    return os;
}
Instruction::~Instruction() = default;

string Instruction::ProcessExpression(string &arguemnt, vector<Register> &registers) {
    string evaluated;

    // -- 0. level: Fix +-

    // -- 1. level: Parentheses --

    // -- 2/a. level: Integer --

        // -- 2/a/1 : PLUS / MINUS --

        // -- 2/a/2 : MULTIPLY / DIVIDE

    // -- 2/b. level: Boolean --

        // -- 2/b/1 : OR --

        // -- 2/b/2 : AND --

        // -- 2/b/3 : EQALS / NOT-EQUALS --

        // -- 2/b/4 : BIGGER / SMALLER / BIGGER-EQUALS / SMALLER-EQUALS --

        // -- 2/b/5 : NOT

    return evaluated;
}






