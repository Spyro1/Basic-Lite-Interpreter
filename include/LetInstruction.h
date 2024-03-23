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
    LetInstruction(int lineNumber, const string& expression);
    // -- Virtual function --
    void Execute(vector<Register>& registers, vector<Instruction*>& instructions, int& instructionIndex) override;
    // -- Destructor --
    ~LetInstruction() override;
};


#endif //NAGYHAZI_LETINSTRUCTION_H
