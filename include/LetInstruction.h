//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_LETINSTRUCTION_H
#define NAGYHAZI_LETINSTRUCTION_H

#include "Instruction.h"

#include "../memtrace.h"

using std::string;

class LetInstruction : public Instruction{
public:
    // -- Constructors --
    LetInstruction(int lineNumber, const string& expression);
    // -- Virtual function --
    virtual void Execute(vector<Register>& registers, vector<Instruction*>& instructions, int& instructionIndex);
    // -- Destructor --
    virtual ~LetInstruction();
};


#endif //NAGYHAZI_LETINSTRUCTION_H
