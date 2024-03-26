//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_INSTRUCTION_H
#define NAGYHAZI_INSTRUCTION_H
#include <vector>
#include "Register.h"

using std::string;
using std::vector;
#define nopos string::npos

// BASIC command keywords
#define LET "let"
#define PRINT "print"
#define IF "if"
#define GOTO "goto"
#define READ "read"

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
    string getInstructionTypeStr() const;
    InstructionType getInstructionType() const;
    string getExpression() const;
    // -- Virtual function --
    virtual void Execute(vector<Register>& registers, vector<Instruction*>& instructions, int& instructionIndex) = 0;
    // -- Operators --
//    bool operator>(const Instruction& rhs) const { return this->lineNumber > rhs.lineNumber; }
//    bool operator<(const Instruction& rhs) const { return  this->lineNumber < rhs.lineNumber; }
//    bool operator>=(const Instruction& rhs) const { return this->lineNumber >= rhs.lineNumber; }
//    bool operator<=(const Instruction& rhs) const { return this->lineNumber <= rhs.lineNumber; }
//    bool operator==(const Instruction& rhs) const { return this->lineNumber == rhs.lineNumber; }
//    bool operator!=(const Instruction& rhs) const { return this->lineNumber != rhs.lineNumber; }
    // -- Destructor --
    virtual ~Instruction() = 0;
protected:
    // -- Protected functions --
    string ProcessExpression(string &argument, vector<Register> &registers);
    void ReplaceCharacters(string &inputStr, const string &searched, const string &replace);
    int CountCharacter(const string &str, char ch);
    string RemoveWhiteSpace(const string& str);
    void SplitAndProcessArguemnts(const string& inputArg, vector<Register>& registers, size_t operatorIndex, float& evaluatedArg1, float& evaluatedArg2, size_t operatorChars = 1) ;
    size_t FindIndexOf(const string &str, char searched);
    size_t FindLastIndexOf(const string &str, char searched);
    size_t FindBracketPairIndex(string str, size_t openPos, char OpenPair = '(', char ClosePair = ')');
    inline bool Exists(size_t value) { return value != nopos; }

};

std::ostream& operator<<(std::ostream& os, const Instruction& inst);


#endif //NAGYHAZI_INSTRUCTION_H
