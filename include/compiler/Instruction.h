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

/**
 * Enum representing different types of instructions.
 */
enum InstructionType { NoType, Print, Let, If, Goto, Read };

/**
 * The base abstract instruction class for other specific instructions for the program interpreter.
 */
class Instruction {

protected:
    int lineNumber = -1;     /// The line number of the instruction.
    string expression;       /// The expression argument of the instruction.
    InstructionType instrTy; /// The type of the instruction.
public:
    // == Constructors ==
    /**
     * Default constructor for arrays
     */
    // Instruction();
    /**
     * Initialize the instruction with the given base values.
     * @param lineNumber_ The line number of the instruction.
     * @param expression_ The expression argument of the instruction.
     * @param instructionType The type of the instruction.
     */
    Instruction(int lineNumber_, const string& expression_, InstructionType instructionType = NoType);
    // == Getters ==
    /**
     * Get the line number of the instruction
     * @return The line number of the instruction.
     */
    int getLineNumber() const;
    /**
    * Get the string representation of the instruction type.
    * @return The string representation of the instruction type.
    */
    string getInstructionTypeStr() const;
    /**
     * Get the type of the instruction.
     * @return The type of the instruction.
     */
    InstructionType getInstructionType() const;
    /**
     * Get the expression argument of the instruction.
     * @return The expression argument of the instruction.
     */
    string getExpression() const;
    // == Virtual function ==
    /**
     * This function must be implemented by derived classes to execute the specific
     * behavior associated with the instruction.
     * @param registers The array of registers.
     * @param instructions The array of instructions.
     * @param instructionIndex The current instruction index.
     */
    virtual void Execute(vector<Register>& registers, vector<Instruction*>& instructions, int& instructionIndex) = 0;
    // == Operators ==
    /**
     * Overloaded stream insertion operator for printing Instruction objects.
     * @param os The output stream.
     * @param inst The Instruction object to be printed.
     * @return A reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Instruction& inst);
    // == Static functions ==
    /**
     * Check if a string represents a valid number.
     * @param str The string to be checked.
     * @return True if the string represents a number, false otherwise.
     */
    static bool isNumber(const string &str);
protected:
    // == Protected functions ==
    /**
     * Process the expression. Splits the expression into tokens based of the allowed operators. Assigns the value
     * to the register if there is an assigning operator in the expression. Returns the registers value if needed, or
     * just a decimal value after evaluation.
     * @param argument The argument to be processed.
     * @param registers The array of registers.
     * @return The evaluated expression.
     */
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