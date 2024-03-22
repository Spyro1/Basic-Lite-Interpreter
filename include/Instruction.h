//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_INSTRUCTION_H
#define NAGYHAZI_INSTRUCTION_H
#include "Register.h"
#include "List.hpp"

#include "../memtrace.h"

enum InstructionType { NoType, Print, Let, If, Goto, Read };

class Instruction {

protected:
    int lineNumber = -1;
    char* expression;
    std::string argument;
    InstructionType instrTy;
public:
    // -- Constructors --
    Instruction();
    Instruction(int lineNumber, const char* expression);
    // -- Getters --
    int getLineNumber() const;
    // -- Virtual function --
    virtual void Execute(List<Register>& registers, List<Instruction>& instructions, int& instructionIndex) = 0;
    // -- Operators --
    bool operator>(const Instruction& rhs) const { return this->lineNumber > rhs.lineNumber; }
    bool operator<(const Instruction& rhs) const { return  this->lineNumber < rhs.lineNumber; }
    bool operator>=(const Instruction& rhs) const { return this->lineNumber >= rhs.lineNumber; }
    bool operator<=(const Instruction& rhs) const { return this->lineNumber <= rhs.lineNumber; }
    bool operator==(const Instruction& rhs) const { return this->lineNumber == rhs.lineNumber; }
    bool operator!=(const Instruction& rhs) const { return this->lineNumber != rhs.lineNumber; }
    // -- Destructor --
    virtual ~Instruction() = 0;
};


#endif //NAGYHAZI_INSTRUCTION_H
