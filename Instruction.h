//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_INSTRUCTION_H
#define NAGYHAZI_INSTRUCTION_H
#include "Register.h"

class Instruction {

protected:
    int lineNumber;
    char* expression;

public:
    // -- Constructors --
    Instruction();
    Instruction(int lineNumber, const char* expression);

    int getLineNumber() const;
    virtual void Execute(Register registers[], size_t registerCount, Instruction instructions[], int& instructionIndex) { }

    virtual ~Instruction();
};


#endif //NAGYHAZI_INSTRUCTION_H
