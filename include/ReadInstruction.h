//
// Created by marci on 2024. 03. 16..
//

#ifndef NAGYHAZI_READINSTRUCTION_H
#define NAGYHAZI_READINSTRUCTION_H

#include "../include/Instruction.h"

#include "../memtrace.h"

class ReadInstruction : public Instruction{
public:
    // -- Constructors --
    ReadInstruction(int lineNumber, const string& expression);
    // -- Virtual function --
    virtual void Execute(List<Register>& registers, List<Instruction>& instructions, int& instructionIndex);
    // -- Destructor --
    virtual ~ReadInstruction();
};

#endif //NAGYHAZI_READINSTRUCTION_H
