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

    // Test for syntax error



    // Test if register name exists. if not, then create new register
    int regIndex = Register::FindRegisterIndex(registers, regName);
    string evaluatedArgument = ProcessExpression(argument, registers);
    auto newValue = stoi(evaluatedArgument);
    if ( regIndex == -1 ) {
        // Create new register and initialize it
        registers.emplace_back(regName, newValue);
    } else {
        // Assign value to existing register
        registers[regIndex].SetValue(newValue);
    }
//    if ()

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
