//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_INSTRUCTION_H
#define NAGYHAZI_INSTRUCTION_H
#include <vector>
#include "Register.h"
#include "List.hpp"

#include "../memtrace.h"

using std::string;
using std::vector;

enum InstructionType { NoType, Print, Let, If, Goto, Read };

class Instruction {

protected:
    int lineNumber = -1;
//    char* expression;
    string expression;
    InstructionType instrTy;
public:
    // -- Constructors --
    Instruction();
    //    Instruction(int lineNumber_, const char* expression_);
    Instruction(int lineNumber_, const string& expression_);
    // -- Getters --
    int getLineNumber() const;
    // -- Virtual function --
    virtual void Execute(vector<Register>& registers, vector<Instruction*>& instructions, int& instructionIndex) = 0;
    // -- Operators --
    bool operator>(const Instruction& rhs) const { return this->lineNumber > rhs.lineNumber; }
    bool operator<(const Instruction& rhs) const { return  this->lineNumber < rhs.lineNumber; }
    bool operator>=(const Instruction& rhs) const { return this->lineNumber >= rhs.lineNumber; }
    bool operator<=(const Instruction& rhs) const { return this->lineNumber <= rhs.lineNumber; }
    bool operator==(const Instruction& rhs) const { return this->lineNumber == rhs.lineNumber; }
    bool operator!=(const Instruction& rhs) const { return this->lineNumber != rhs.lineNumber; }


    std::ostream& operator<<(std::ostream& os);
    // -- Destructor --
    virtual ~Instruction() = 0;
};
//bool CompareInstructions(Instruction& a,Instruction& b) { return (a.getLineNumber() < b.getLineNumber());}


#endif //NAGYHAZI_INSTRUCTION_H
