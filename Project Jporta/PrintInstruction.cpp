//
// Created by Szenes Márton on 2024. 03. 14..
//
#include <iostream>
#include <cstring>
#include "memtrace.h"
#include "PrintInstruction.h"

PrintInstruction::PrintInstruction(int lineNumber, const string& expression) : Instruction(lineNumber, expression, Print) {}

void PrintInstruction::Execute(vector<Register> &registers, vector<Instruction*>& instructions, int& instructionIndex) {
    using namespace std;
    if (!expression.empty()){
        // If expression is a string
        int doubleComma = CountCharacter(expression, '"');
        // The expression is a register
        if (doubleComma == 0){
            //  Remove whitespace
            string shortExpression = RemoveWhiteSpace(expression);
            string evaluated = ProcessExpression(shortExpression, registers);
            try{
                cout << stof(evaluated);
            } catch (std::exception& e){
                throw SyntaxError("Can not recognize \"" + expression + "\" as a print argument", lineNumber);
            }
        }
        else if (doubleComma % 2 == 0){
            size_t begining = expression.find_first_of('"');
            size_t ending = expression.find_last_of('"');
            string cutted = expression.substr(begining+1,ending - begining - 1 );
            cutted = regex_replace(cutted, std::regex("\\n"), "\n");
            cutted = regex_replace(cutted, std::regex("\\t"), "\t");
            cutted = regex_replace(cutted, std::regex("\\\""), "\"");
            cout << cutted;
        }
        else
            throw SyntaxError("Wrong string literal", lineNumber);
    }
    instructionIndex++;
}

int PrintInstruction::CountCharacter(const string& str, char ch) {
    int count = 0;
    for (size_t i = 0; i < str.length(); i++)
        if (str[i] == ch)
            count++;
    return count;
}