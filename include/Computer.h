//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_COMPUTER_H
#define NAGYHAZI_COMPUTER_H

#include "Instruction.h"
#include "Register.h"
#include "List.hpp"

#include "../memtrace.h"

#define DEBUG_

// BASIC command keywords
#define LET "let"
#define PRINT "print"
#define IF "if"
#define GOTO "goto"
#define THEN "then"
#define READ "read"
#define RUN "run"

class Computer {
    List<Register> registers;       // List of registers
    List<Instruction> instructions; // List of instructions line by line
    int instructionIndex = -1;      // Current Instruction index
public:
    // -- Constructor --
    /**
     * Creates a computer object that can run a BASIC-lite program.
     * @param registerCount Number of registers to make the computer with. (Default value is 2: a, i)
     */
    explicit Computer(size_t registerCount = 2);
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
     *
     */
    void RunProgram();
    // -- Destructor --
    ~Computer();

private:
    // -- Private functions--
    void ExecuteNextInstruction();
    void DeleteProgramArrays();
    void ProcessProgramLine(const string& inputLine);
    void SplitLineToTokens(const string& inputLine, int& lineNumber, string& command, string& expression);
};


#endif //NAGYHAZI_COMPUTER_H
