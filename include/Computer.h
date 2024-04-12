//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_COMPUTER_H
#define NAGYHAZI_COMPUTER_H

#include <vector>
#include "Instruction.h"
#include "Register.h"

class Computer {
    std::vector<Register> registers;       // List of registers
    std::vector<Instruction*> instructions; // List of instructions line by line
    int instructionIndex = -1;      // Current Instruction index
public:
    // -- Constructor --
    /**
     * Creates a computer object that can run a BASIC-lite program.
     */
    explicit Computer();
    // -- Getters --
    /**
     * Gives the number of instructions in the program
     * @return Number of instructions
     */
    size_t getInstructionCount() const;
    // -- Functions --
    /**
     * Reads the program from the given file into the 'instructions' list.
     * @param filename The name of the file that contains the program.
     */
    void ReadProgramFromFile(const string& filename);
//    void ReadProgramFromString(char* program);
    /**
     * Evaluates the read character string line.
     * If the line number is positive, then the computer adds it to the instruction list,
     * if the number is negative, then the computer removes the corresponding instrcution
     * wtih the absolute value of the given line number.
     * @param programLine Inputed line containing the instruction: <lineNumber> <command> <argument>
     */
    void NewInstruction(const string& programLine);
    /**
     *  Runs the program: Executes the instructions based on the instructionIndex value
     *  which is modified according to the previous instrcution.
     */
    void RunProgram();
    /**
     * Clears the list of instructions from the program memory and resets the instruction count to 0.
     */
    void ClearProgram();
    /**
     * Lists the instructions strored in the memory of the computer.
     * @return Returns a string containing all the instructions displayed line by line.
     */
    friend std::ostream& operator<<(std::ostream& os, const Computer& pc);

    // -- Destructor --
    ~Computer();
    /**
     * Converts the string to upper case letters
     * @param str Input string
     * @return Upper case lettered string
     */
    static string ToUpperCaseStr(const string &str);

private:
    // -- Private functions--
    /**
     * Executes the next instruction in the line based on the instrcutionIndex's value
     */
    void ExecuteNextInstruction();
    /**
     * Evaluates the inputed line. Seperates the input line to tokens (line number, instruction, argument),
     * and adds the new instrcutin to the list.
     * @param inputLine New instruction line: <id> <instruction> <parameter>
     */
    void ProcessProgramLine(const string& inputLine);
    /**
     *
     * @param inputLine
     * @param lineNumber
     * @param command
     * @param expression
     */
    void SplitLineToTokens(const string& inputLine, int& lineNumber, string& command, string& expression);
    /**
     *
     */
    void ClearInstructions();
    /**
     *
     */
    void SortInstructions();
    /**
     *
     * @param lineNumber
     */
    void RemoveInstruction(int lineNumber);
    /**
     *
     * @param a
     * @param b
     * @return
     */
    static bool CompareInstructions(const Instruction *a, const Instruction *b);
};


#endif //NAGYHAZI_COMPUTER_H
