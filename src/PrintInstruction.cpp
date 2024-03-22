//
// Created by Szenes Márton on 2024. 03. 14..
//
#include <iostream>
#include <cstring>
#include "../include/PrintInstruction.h"

PrintInstruction::PrintInstruction(int lineNumber, const string& expression) : Instruction(lineNumber, expression) {
    instrTy = InstructionType::Print;
}
// -- Virtual function --
void PrintInstruction::Execute(List<Register> &registers, List<Instruction>& instructions, int& instructionIndex) {
    using namespace std;
    // If expression is a string
    int doubleComma = 0;
    int i = 0;
    while(expression[i] != '\0') {
        if (expression[i] == '"') doubleComma++;
        i++;
    }
    if (doubleComma == 1 || doubleComma > 2)
        throw runtime_error(string("Wrong string literal in line: ") + to_string(lineNumber));
    if (doubleComma == 2) {
        char* defExpression = new char[expression.length()+1];
        strcpy(defExpression, expression.c_str());
        defExpression[strlen(defExpression)-1] = 0; // Cut " from the end
        defExpression++;                           // Cut " from the beginning of the string
        cout << defExpression << endl;             // Print string
        defExpression--;
        delete[] defExpression;
    }
    // Else the expression is a variable
    else {
        int regindex = 0;
        while (regindex < registers.getCount() && registers[regindex]->getName() != expression)
        { regindex++; }
        // Error handling if unrecognized variable was in expression
        if (regindex >= registers.getCount()){
            throw logic_error(string("Syntax error: Unrecognized variable in line: ") + to_string(lineNumber));
        }
        else{
            cout << registers[regindex]->getValue() << endl;
        }
    }
    instructionIndex++;
}
PrintInstruction::~PrintInstruction() {
//    delete[] expression;
}
