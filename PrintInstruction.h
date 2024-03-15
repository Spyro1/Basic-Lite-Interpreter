//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_PRINTINSTRUCTION_H
#define NAGYHAZI_PRINTINSTRUCTION_H

#include "Instruction.h"

class PrintInstruction : public Instruction {
    // -- Constructors --
    PrintInstruction(int lineNumber, const char* expression);
    // -- Virtual function --
    virtual void Execute(Register registers[], size_t registerCount, Instruction instructions[], int& instructionIndex);
};


#endif //NAGYHAZI_PRINTINSTRUCTION_H
