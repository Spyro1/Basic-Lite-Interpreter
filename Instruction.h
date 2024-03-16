//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_INSTRUCTION_H
#define NAGYHAZI_INSTRUCTION_H
#include "Register.h"
#include "List.h"

class Instruction {

protected:
    int lineNumber;
    char* expression;

public:
    // -- Constructors --
    Instruction();
    Instruction(int lineNumber, const char* expression);
    // -- Getters --
    int getLineNumber() const;
    // -- Virtual function --
    virtual void Execute(List<Register>& registers, List<Instruction>& instructions, int& instructionIndex) { }

    virtual ~Instruction();
};


#endif //NAGYHAZI_INSTRUCTION_H
