//
// Created by marci on 2024. 03. 16..
//

#include <stdexcept>
#include <algorithm>
#include "../../include/compiler/GotoInstruction.h"

GotoInstruction::GotoInstruction(int lineNumber, const string& expression) : Instruction(lineNumber, expression, Goto) {}

void GotoInstruction::Execute(vector<Register> &registers, vector<Instruction*>& instructions, int &instructionIndex) {
    using namespace std;
    int jumpNumber;
    try{
        jumpNumber = std::stoi(expression); // Try to parse to int
    } catch (std::exception& e){
        throw SyntaxError("Can not recognize \"" + expression + "\" as a goto argument", lineNumber);
    }
    size_t i = 0;
    bool found = false;
    while (i < instructions.size() && !found) {
        if (instructions[i]->getLineNumber() == jumpNumber) {
            instructionIndex = (int)i;
            found = true;
        }
        i++;
    }
    if (!found) throw CompileError("No line identifier found to jump to", lineNumber);
}