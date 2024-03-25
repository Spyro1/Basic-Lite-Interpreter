//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_PRINTINSTRUCTION_H
#define NAGYHAZI_PRINTINSTRUCTION_H

#include "Instruction.h"

class PrintInstruction : public Instruction {
public:
    // -- Constructors --
    PrintInstruction(int lineNumber, const string& expression);
    // -- Virtual function --
    void Execute(vector<Register>& registers, vector<Instruction*>& instructions, int& instructionIndex) override;
    // -- Destructor --
    ~PrintInstruction() override;
};


#endif //NAGYHAZI_PRINTINSTRUCTION_H
