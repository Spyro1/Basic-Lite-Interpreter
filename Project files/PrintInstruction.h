//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_PRINTINSTRUCTION_H
#define NAGYHAZI_PRINTINSTRUCTION_H

#include "Instruction.h"

/**
 * The PrintInstruction class represents an instruction to print value to the output. It inherits from the Instruction class.
 */
class PrintInstruction : public Instruction {
public:

    // == Constructors ==
    /**
     * This constructor initializes a new instance of the PrintInstruction class, which represents an instruction
     * for printing output to the console. It inherits from the Instruction class.
     * @param lineNumber An integer representing the line number in the code where this instruction occurs.
     * It helps with debugging and tracing execution flow.
     * @param expression A constant reference to a string representing the content or message to be printed.
     * This could include variables, literals, or expressions that need to be evaluated and printed.
     */
    PrintInstruction(int lineNumber, const string& expression);

    // == Virtual function ==
    /**
     * This function is a virtual method intended to execute a specific instruction within a sequence of instructions.
     * It operates on a set of registers and a list of instruction objects, moving through the instructions based on
     * the provided instruction index.
     * @param registers A reference to a map representing register names and values of the computer.
     * These registers hold data that the instructions may operate on or modify.
     * @param instructions A reference to a vector of pointers to Instruction objects.
     * These represent the sequence of instructions to be executed.
     * @param instructionIndex A reference to an integer representing the current index of the instruction to be
     * executed within the instructions vector. This index will be updated to point to the next instruction to
     * execute after this function call.
     */
    void Execute(std::map<string, float>& registers, vector<Instruction*>& instructions, int& instructionIndex) override;
private:
    /**
     * Counts the occurrences of a specific character in a string.
     * @param str The input string to search for occurrences.
     * @param ch The character to count occurrences of.
     * @return The count of occurrences of the specified character in the string.
     */
    int CountCharacter(const string &str, char ch);

};


#endif //NAGYHAZI_PRINTINSTRUCTION_H
