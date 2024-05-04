//
// Created by marci on 2024. 03. 16..
//

#include <stdexcept>
#include <algorithm>
#include "../../memtrace.h"
#include "../../include/compiler/GotoInstruction.h"

GotoInstruction::GotoInstruction(int lineNumber, const string& expression) : Instruction(lineNumber, expression, Goto) {}

void GotoInstruction::Execute(vector<Register> &registers, vector<Instruction*>& instructions, int &instructionIndex) {
    using namespace std;
    int jumpNumber;

    string shortExpression = RemoveWhiteSpace(expression); //  Remove whitespace
    string evaluated = ProcessExpression(shortExpression, registers); // Process the expression
    try{
        jumpNumber = stoi(evaluated); // Convert to number if can
    } catch (std::exception& e){
        throw CompileError("Can not recognize \"" + expression + "\" as a goto argument", lineNumber);
    }
    size_t i = 0;
    // Search instruction index to jump to
    while (i < instructions.size()) {
        if (instructions[i]->getLineNumber() == jumpNumber) {
            instructionIndex = (int)i;
            break;
        }
        i++;
    }
    if (i >= instructions.size()) throw SyntaxError("No line identifier found to jump to", lineNumber);
}