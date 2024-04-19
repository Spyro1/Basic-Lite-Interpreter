//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_INSTRUCTION_H
#define NAGYHAZI_INSTRUCTION_H
#include <vector>
#include "Register.h"
#include "../exceptions/SyntaxError.h"
#include "../exceptions/CompileError.h"
#include "../exceptions/UniqueError.h"


using std::string;
using std::vector;
#define nopos string::npos

// BASIC command keywords
#define LET "LET"
#define PRINT "PRINT"
#define IF "IF"
#define GOTO "GOTO"
#define READ "READ"

enum InstructionType { NoType, Print, Let, If, Goto, Read };

class Instruction {

protected:
    int lineNumber = -1;
    string expression;
    InstructionType instrTy;
public:
    // -- Constructors --
    Instruction();
    Instruction(int lineNumber_, const string& expression_, InstructionType instructionType = NoType);
    // -- Getters --
    int getLineNumber() const;
    string getInstructionTypeStr() const;
    InstructionType getInstructionType() const;
    string getExpression() const;
    // -- Virtual function --
    virtual void Execute(vector<Register>& registers, vector<Instruction*>& instructions, int& instructionIndex) = 0;
    // -- Operators --
    friend std::ostream& operator<<(std::ostream& os, const Instruction& inst);
    // -- Static functions --
    static bool isNumber(const string &str);
    // -- Destructor --
    virtual ~Instruction();
protected:
    // -- Protected functions --
    string ProcessExpression(string &argument, vector<Register> &registers);
    void ReplaceCharacters(string &inputStr, const string &searched, const string &replace);
    int CountCharacter(const string &str, char ch);
    string RemoveWhiteSpace(const string& str);
    void SplitAndProcessArguments(const string& inputArg, vector<Register>& registers, size_t operatorIndex, float& evaluatedArg1, float& evaluatedArg2, size_t operatorChars = 1) ;
    size_t FindBracketPairIndex(string str, size_t openPos, char OpenPair = '(', char ClosePair = ')');
    static size_t FindRegisterIndex(const std::vector<Register> &registers, const string &name);
    static inline bool Exists(size_t value) { return value != nopos; }
};

#endif //NAGYHAZI_INSTRUCTION_H