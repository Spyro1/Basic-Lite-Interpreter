//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_PRINTINSTRUCTION_H
#define NAGYHAZI_PRINTINSTRUCTION_H

#include "Instruction.h"

#include "../memtrace.h"

class PrintInstruction : public Instruction {
public:
    // -- Constructors --
    PrintInstruction(int lineNumber, const string& expression);
    // -- Virtual function --
    virtual void Execute(vector<Register>& registers, vector<Instruction*>& instructions, int& instructionIndex);
    // -- Destructor --
    virtual ~PrintInstruction();
private:
    void PrintToConsole(const string& expression);
    void ReplaceCharacters(string& inputStr, const string& searched, const string& replace);
};


#endif //NAGYHAZI_PRINTINSTRUCTION_H
