//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_COMPUTER_H
#define NAGYHAZI_COMPUTER_H

#include <vector>
#include <map>

#include "Instruction.h"
#include "LetInstruction.h"
#include "PrintInstruction.h"
#include "IfInstruction.h"
#include "GotoInstruction.h"
#include "ReadInstruction.h"

/**
 * Represents a computer object for running a BASIC-lite program and interpreting it.
 */
class Computer {
    std::map<std::string, float> registers; // Map of registers
    std::vector<Instruction*> instructions; // List of instructions line by line
    int instructionIndex = -1;              // Current Instruction index
public:

    // == Constructor ==
    /**
     * Creates a computer object that can run a BASIC-lite program.
     */
    Computer();

    // == Destructor ==
    /**
     * Destroys the computer object.
     */
    ~Computer();

    // == Getters ==
    /**
     * Gives the number of instructions in the program
     * @return Number of instructions
     */
    size_t getInstructionCount() const;

    // == Functions ==
    /**
     * Reads the program from the given file into the 'instructions' vector.
     * @param filename The name of the file that contains the program.
     */
    void ReadProgramFromFile(const string& filename);
    /**
     * Saves the program from the 'instructions' vector into a file.
     * @param filename The name of the file to save the program into.
     */
    void SaveProgramToFile(const string& filename);
    /**
     * Evaluates the read character string line.
     * If the line number is positive, then the computer adds it to the instruction list,
     * if the number is negative, then the computer removes the corresponding instrcution
     * with the absolute value of the given line number.
     * @param programLine Inputted line containing the instruction: <lineNumber> <command> <argument>
     */
    void NewInstruction(const string& programLine);
    /**
     *  Runs the program: Executes the instructions based on the instructionIndex value
     *  which is modified according to the previous instruction.
     */
    void RunProgram();
    /**
     * Clears the list of instructions from the program memory and resets the instruction count to 0.
     */
    void ClearProgram();
    /**
     * Lists the instructions stored in the memory of the computer.
     * @return Returns a string containing all the instructions displayed line by line.
     */
    friend std::ostream& operator<<(std::ostream& os, const Computer& pc);
    /**
     * Converts the string to upper case letters
     * @param str Input string
     * @return Upper case lettered string
     */
    static string ToUpperCaseStr(const string &str);
private:

    // == Private functions==
    /**
     * Evaluates the inputed line. Seperates the input line to tokens (line number, instruction, argument),
     * and adds the new instrcutin to the list.
     * @param inputLine New instruction line: <id> <instruction> <parameter>
     */
    void ProcessProgramLine(const string& inputLine);
    /**
     * Splits a line of input into tokens representing different parts of a command.
     * @param inputLine The input line to split.
     * @param lineNumber Reference to an integer to store the line number.
     * @param command Reference to a string to store the command token.
     * @param expression Reference to a string to store the expression token.
     */
    void SplitLineToTokens(const string& inputLine, int& lineNumber, string& command, string& expression);
    /**
     * Clears all instructions stored in the computer's memory.
     */
    void ClearInstructions();
    /**
     * Sorts the instructions stored in the computer's memory.
     */
    void SortInstructions();
    /**
     * Removes an instruction with the specified line number.
     * @param lineNumber The line number of the instruction to remove.
     */
    void RemoveInstruction(int lineNumber);

};


#endif //NAGYHAZI_COMPUTER_H
