//
// Created by Szenes Márton on 2024. 03. 14..
//

#include <algorithm>
#include <vector>
#include "../include/LetInstruction.h"


LetInstruction::LetInstruction(int lineNumber, const string& expression) : Instruction(lineNumber, expression) {
    instrTy = InstructionType::Let;
}

void LetInstruction::Execute(vector<Register> &registers, vector<Instruction*> &instructions, int &instructionIndex) {
    using namespace std;
    string shortExpression = expression;
    //  Remove spaces using erase and remove_if
    shortExpression.erase(std::remove_if(shortExpression.begin(), shortExpression.end(), ::isspace), shortExpression.end());
    size_t equalSignIndex = shortExpression.find('=');
    string regName = shortExpression.substr(0, equalSignIndex); // Get register name
    string argument = shortExpression.substr(equalSignIndex + 1); // Separate after the equal sign


//    if ()

    // a = 12       // INT literal
    // a = a + 1    // ADD
    // a = a - 1    // SUB
    // a = a * 1    // MULTIPLY
    // a = a / 1    // DEVIDE
    // a = (3 + a) * a  // BRACKETS
    instructionIndex++;
}
LetInstruction::~LetInstruction() {

}


// -- Private helper functions --
void LetInstruction::ProcessExpression(string &expression, vector<Register> &registers) {

}
