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
void PrintInstruction::Execute(vector<Register> &registers, vector<Instruction*>& instructions, int& instructionIndex) {
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
//        char* cuttedExpression = new char[expression.length() + 1];
//        strcpy(cuttedExpression, expression.c_str());
//        cuttedExpression[strlen(cuttedExpression) - 1] = 0; // Cut " from the end
//        cuttedExpression++;                           // Cut " from the beginning of the string
        string cutted = expression.substr(1,expression.length()-2);
        ReplaceCharacters(cutted, "\\n", "\n");
        ReplaceCharacters(cutted, "\\t", "\t");
        PrintToConsole(cutted);             // Print string
//        cuttedExpression--;
//        delete[] cuttedExpression;
    }
    // Else the expression is a variable
    else {
        int regindex = 0;
        while ((size_t)regindex < registers.size() && registers[regindex].getName() != expression)
        { regindex++; }
        // Error handling if unrecognized variable was in expression
        if ((size_t)regindex >= registers.size()){
            throw logic_error(string("Syntax error: Unrecognized variable in line: ") + to_string(lineNumber));
        }
        else{
            PrintToConsole(to_string(registers[regindex].getValue()));
        }
    }
    instructionIndex++;
}
void PrintInstruction::PrintToConsole(const string& expression){
    std::cout << expression;// << std::endl;

}
void PrintInstruction::ReplaceCharacters(string& inputStr, const string& searched, const string& replace){
    size_t pos = 0;
    while ((pos = inputStr.find(searched, pos)) != std::string::npos) {
        inputStr.replace(pos, searched.length(), replace);
        pos += replace.length();
    }
}
PrintInstruction::~PrintInstruction() {
//    delete[] expression;
}
