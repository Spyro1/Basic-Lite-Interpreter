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
    IfInstruction(int lineNumber, const string& expression);
    // -- Virtual function --
    void Execute(vector<Register>& registers, vector<Instruction*>& instructions, int& instructionIndex) override;
    // -- Destructor --
    ~IfInstruction() override;
};


#endif //NAGYHAZI_IFINSTRUCTION_H
