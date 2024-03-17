//
// Created by marci on 2024. 03. 16..
//

#ifndef NAGYHAZI_IFINSTRUCTION_H
#define NAGYHAZI_IFINSTRUCTION_H

#include "../include/Instruction.h"

#include "../memtrace.h"

class IfInstruction : public Instruction{
public:
    // -- Constructors --
    IfInstruction(int lineNumber, const char* expression);
    // -- Virtual function --
    virtual void Execute(List<Register>& registers, List<Instruction>& instructions, int& instructionIndex);
    // -- Destructor --
    virtual ~IfInstruction();
};


#endif //NAGYHAZI_IFINSTRUCTION_H
