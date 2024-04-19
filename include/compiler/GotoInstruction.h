//
// Created by marci on 2024. 03. 16..
//

#ifndef NAGYHAZI_GOTOINSTRUCTION_H
#define NAGYHAZI_GOTOINSTRUCTION_H

#include "Instruction.h"

class GotoInstruction : public Instruction{
public:
    // -- Constructors --
    GotoInstruction(int lineNumber, const string& expression);
    // -- Virtual function --
    void Execute(vector<Register>& registers, vector<Instruction*>& instructions, int& instructionIndex) override;
    // -- Destructor --
    ~GotoInstruction() override;
};

#endif //NAGYHAZI_GOTOINSTRUCTION_H