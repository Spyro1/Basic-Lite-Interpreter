//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_LETINSTRUCTION_H
#define NAGYHAZI_LETINSTRUCTION_H

#include "Instruction.h"

#include "../memtrace.h"

class LetInstruction : public Instruction{
public:
    // -- Constructors --
    LetInstruction(int lineNumber, const char* expression);
    // -- Virtual function --
    virtual void Execute(List<Register>& registers, List<Instruction>& instructions, int& instructionIndex);
};


#endif //NAGYHAZI_LETINSTRUCTION_H
