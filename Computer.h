//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_COMPUTER_H
#define NAGYHAZI_COMPUTER_H

#include "Instruction.h"
#include "Register.h"
#include "List.h"

class Computer {
    List<Register> registers;
    List<Instruction> instructions;
    int instructionIndex = -1;
public:
    explicit Computer(size_t registerCount = 2);

    void ReadProgramFromFile(const char* filename);
//    void ReadProgramFromString(char* program);
    void RunProgram();
    void ExecuteNextInstruction();

    ~Computer();

private:
    void DeleteProgramArrays();

};


#endif //NAGYHAZI_COMPUTER_H
