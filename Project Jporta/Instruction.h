//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_INSTRUCTION_H
#define NAGYHAZI_INSTRUCTION_H
#include <vector>
#include "Register.h"
#include "SyntaxError.h"s
#include "UniqueError.h"


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
    // == Destructor ==
    /**
    * Destroys the Instruction object.
    */
    virtual ~Instruction() = default;
protected:
    // == Expression evaluating function ==
    /**
     * Process the expression. Splits the expression into tokens based of the allowed operators. Assigns the value
     * to the register if there is an assigning operator in the expression. Returns the registers value if needed, or
     * just a decimal value after evaluation.
     * @param argument The argument to be processed.
     * @param registers The array of registers.
     * @return The evaluated expression.
     */
    string ProcessExpression(string &argument, vector<Register> &registers);

    // == Helper functions ==
    /**
     * Removes all whitespace characters from a string.
     * @param str The input string to remove whitespace from.
     * @return A new string with all whitespace characters removed.
     */
    string RemoveWhiteSpace(const string& str);

    /**
     * @brief Finds the index of a register in a vector of registers by name.
     *
     * @param registers The vector of registers to search in.
     * @param name The name of the register to find.
     * @return The index of the register if found, otherwise returns nopos.
     */
    static size_t FindRegisterIndex(const std::vector<Register> &registers, const string &name);

    /**
     * Checks if a value exists (not equal to std::string::npos).
     * @param value The value to check for existence.
     * @return true if the value exists, false otherwise.
     */
    static inline bool Exists(size_t value) { return value != nopos; }
private:

    /**
     * Replaces all occurrences of characters in a string with specified replacements.
     * @param inputStr The input string where replacements are performed.
     * @param searched The characters to search for in the input string.
     * @param replace The replacements for the searched characters.
     */
    void ReplaceCharacters(string &inputStr, const string &searched, const string &replace);

    /**
     * Splits an input argument string and processes the individual arguments.
     * @param inputArg The input argument string to split and process.
     * @param registers A vector of registers.
     * @param operatorIndex The index of the operator in the input argument.
     * @param evaluatedArg1 The first evaluated argument after splitting.
     * @param evaluatedArg2 The second evaluated argument after splitting.
     * @param operatorChars The number of characters representing the operator (default: 1).
     */
    void SplitAndProcessArguments(const string& inputArg, vector<Register>& registers, size_t operatorIndex, float& evaluatedArg1, float& evaluatedArg2, size_t operatorChars = 1);

    /**
     * Finds the index of the closing bracket corresponding to an opening bracket in a string.
     * @param str The input string where to search for the bracket pair.
     * @param openPos The position of the opening bracket.
     * @param OpenPair The opening bracket character (default: '(').
     * @param ClosePair The closing bracket character (default: ')').
     * @return The index of the closing bracket.
     */
    size_t FindBracketPairIndex(string str, size_t openPos, char OpenPair = '(', char ClosePair = ')');

};

#endif //NAGYHAZI_INSTRUCTION_H