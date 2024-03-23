//
// Created by Szenes Márton on 2024. 03. 14..
//
#include <iostream>
#include <iomanip>
#include <cstring>
#include "../include/PrintInstruction.h"

PrintInstruction::PrintInstruction(int lineNumber, const string& expression) : Instruction(lineNumber, expression) {
    instrTy = InstructionType::Print;
}
// -- Virtual function --
void PrintInstruction::Execute(vector<Register> &registers, vector<Instruction*>& instructions, int& instructionIndex) {
    using namespace std;
    // If expression is a string
    int doubleComma = CountCharacter(expression, '"');
    // The expression is a register
    if (doubleComma == 0){
        size_t regindex = 0;
        while (regindex < registers.size() && registers[regindex].getName() != expression)
        { regindex++; }
        // Error handling if unrecognized variable was in expression
        if (regindex >= registers.size()){
            throw logic_error(string("Syntax error: Unrecognized variable in line: ") + to_string(lineNumber));
        }
        else{
//            PrintToConsole(to_string(registers[regindex].getValue()));
            cout << registers[regindex].getValue();
        }
    }
    else if (doubleComma % 2 == 0){
        size_t begining = expression.find_first_of('"');
        size_t ending = expression.find_last_of('"');
        string cutted = expression.substr(begining+1,ending - begining - 1 );
        ReplaceCharacters(cutted, "\\n", "\n");
        ReplaceCharacters(cutted, "\\t", "\t");
        ReplaceCharacters(cutted, "\\\"", "\"");
        PrintToConsole(cutted);
    }
    else
        throw runtime_error(string("Wrong string literal in line: ") + to_string(lineNumber));
    instructionIndex++;
}
void PrintInstruction::PrintToConsole(const string& expression){
    std::cout << expression;// << std::endl;

}

PrintInstruction::~PrintInstruction() = default;