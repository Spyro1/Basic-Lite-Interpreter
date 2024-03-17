//
// Created by Szenes Márton on 2024. 03. 14..
//
#include <iostream>
#include <cstring>
#include "../include/PrintInstruction.h"

PrintInstruction::PrintInstruction(int lineNumber, const char *expression) : Instruction(lineNumber, expression) {
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
        expression[strlen(expression)-1] = 0; // Cut " from the end
        expression++;                           // Cut " from the beginning of the string
        cout << expression << endl;             // Print string
    }
    // Else the expression is a variable
    else {
        int regindex = 0;
        while (strcmp(registers[regindex]->getName(), expression) == 0) { regindex++; }
        // Error handling if unrecognized variable was in expression
        if ((size_t)regindex >= registers.Count){
            throw runtime_error(string("Unrecognized variable in line: ") + to_string(lineNumber));
        }
        else{
            cout << registers[regindex]->getValue() << endl;
        }
    }
    instructionIndex++;
}
PrintInstruction::~PrintInstruction() {
    delete[] expression;
}
