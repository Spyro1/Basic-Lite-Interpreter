//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_COMPUTER_H
#define NAGYHAZI_COMPUTER_H

#include "Instruction.h"
#include "Register.h"
#include "List.h"

#include "../memtrace.h"

#define DEBUG

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
    void ReadProgramFromFile(const char* filename);
//    void ReadProgramFromString(char* program);
    void RunProgram();
    void ExecuteNextInstruction();
    // -- Destructor --
    ~Computer();

private:
    // -- Private functions--
    void DeleteProgramArrays();
    void SplitLineToTokens(const std::string& line, int& lineNumber, std::string& command, char** expression);
};


#endif //NAGYHAZI_COMPUTER_H
