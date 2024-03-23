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

enum ReturnType { Void, Integer, Boolean};

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
    string getType() const;
    string getExpression() const;
    // -- Virtual function --
    virtual void Execute(vector<Register>& registers, vector<Instruction*>& instructions, int& instructionIndex) = 0;
    // -- Operators --
    bool operator>(const Instruction& rhs) const { return this->lineNumber > rhs.lineNumber; }
    bool operator<(const Instruction& rhs) const { return  this->lineNumber < rhs.lineNumber; }
    bool operator>=(const Instruction& rhs) const { return this->lineNumber >= rhs.lineNumber; }
    bool operator<=(const Instruction& rhs) const { return this->lineNumber <= rhs.lineNumber; }
    bool operator==(const Instruction& rhs) const { return this->lineNumber == rhs.lineNumber; }
    bool operator!=(const Instruction& rhs) const { return this->lineNumber != rhs.lineNumber; }
    // -- Destructor --
    virtual ~Instruction() = 0;
    // -- Static functions --
    static string ProcessExpression(string &argument, vector<Register> &registers);
};

std::ostream& operator<<(std::ostream& os, const Instruction& inst);

#endif //NAGYHAZI_INSTRUCTION_H
