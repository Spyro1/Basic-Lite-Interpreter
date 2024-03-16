//
// Created by marci on 2024. 03. 16..
//

#ifndef NAGYHAZI_GOTOINSTRUCTION_H
#define NAGYHAZI_GOTOINSTRUCTION_H

#include "../include/Instruction.h"

#include "../memtrace.h"

class GotoInstruction : public Instruction{
public:
    // -- Constructors --
    GotoInstruction(int lineNumber, const char* expression);
    // -- Virtual function --
    virtual void Execute(List<Register>& registers, List<Instruction>& instructions, int& instructionIndex);
};


#endif //NAGYHAZI_GOTOINSTRUCTION_H
