//
// Created by marci on 2024. 03. 16..
//

#ifndef NAGYHAZI_READINSTRUCTION_H
#define NAGYHAZI_READINSTRUCTION_H

#include "../include/Instruction.h"

class ReadInstruction : public Instruction{
public:
    // -- Constructors --
    ReadInstruction(int lineNumber, const string& expression);
    // -- Virtual function --
    void Execute(vector<Register>& registers, vector<Instruction*>& instructions, int& instructionIndex) override;
    // -- Destructor --
    ~ReadInstruction() override;
};

#endif //NAGYHAZI_READINSTRUCTION_H
