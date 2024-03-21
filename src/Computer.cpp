//
// Created by Szenes Márton on 2024. 03. 14..
//
#include <fstream>
#include <iostream>
#include <cstring>
#include "../include/Computer.h"
#include "../include/LetInstruction.h"
#include "../include/PrintInstruction.h"
#include "../include/IfInstruction.h"
#include "../include/GotoInstruction.h"
#include "../include/ReadInstruction.h"


Computer::Computer(size_t registerCount) {
    if (registerCount <  2) throw "Error: There are not enough registers for the computer to work."; // Computer can not work with less than 2 registers. (PLAN)
    // Adding default registers
    registers.Clear();
    registers.Add(new Register("a")); // Base register
    registers.Add(new Register("i")); // Counter
    instructions.Clear();
}

void Computer::ReadProgramFromFile(const char *filename) {
    using namespace std;
    // If this computer has read a program before, then free dynamic memory from registers and istructions
    DeleteProgramArrays();
    // Read file
    fstream filereader;
    filereader.open(filename,ios::in); // Open file
    // If file doesn't exist, then throw exception
    if (!filereader.is_open()){
        filereader.close();
        throw runtime_error("File not found!");
    }
    // File opened, read in file:
    string line;
    while (std::getline(filereader, line, '\n')) {
        ProcessProgramLine(line);
    }

    filereader.close(); // Close File
    instructionIndex = 0;
    // Make instruction in order based on the line number
    instructions.Sort();
}
void Computer::NewInstruction(const char *instructionLine) {

}
void Computer::RunProgram() {
    while (instructionIndex < instructions.getCount()){
        ExecuteNextInstruction();
    }
}

void Computer::ExecuteNextInstruction() {
    instructions[instructionIndex]->Execute(registers,instructions,instructionIndex);
}

void Computer::DeleteProgramArrays() {
    instructions.Clear();
    instructionIndex = -1;
}
Computer::~Computer() {
    //DeleteProgramArrays();
}
void Computer::ProcessProgramLine(const std::string& line) {
    int lineNumber = 0;
    char *expression = nullptr;
    std::string command;

    SplitLineToTokens(line, lineNumber, command, &expression);

    if (command == LET) {
        instructions.Add(new LetInstruction(lineNumber, expression));
    }
    else if (command == PRINT) {
        instructions.Add(new PrintInstruction(lineNumber, expression));
    }
    else if (command == IF) {
        instructions.Add(new IfInstruction(lineNumber, expression));
//            filereader >> command >> expression;
//            #ifdef DEBUG
//                std::cout << "\t> " << command << ": " << expression << std::endl; // Debug
//            #endif
    }
    else if(command == GOTO) {
        instructions.Add(new GotoInstruction(lineNumber, expression));
    }
    else if (command == READ) {
        instructions.Add(new ReadInstruction(lineNumber, expression));
    }
//        else if (command == RUN)
//        instructions.Add(new Instruction())
    delete[] expression;
}
void Computer::SplitLineToTokens(const std::string& line, int &lineNumber, std::string &command, char** expression) {
    // Convert string line to char*
    char* cline = new char[line.length()+1];
    std::strcpy(cline, line.c_str());
    int k = 0;
    // This code snippet is based on this example: https://cplusplus.com/reference/string/string/c_str/
    char* p = std::strtok (cline," ");
    std::string argument;
    while (p != nullptr) {
        if (k == 0) lineNumber = std::stoi(p); // Extract line number
        else if (k == 1) command = std::string(p); // Extract command
        else if (k > 1) argument += std::string(p); // Extract argument
        // std::cout << p << endl;
        p = std::strtok(nullptr," ");
        k++;
    }
    // End of code snippet
    // Convert argument to char* expression
    *expression = new char[argument.length()+1];
    std::strcpy(*expression, argument.c_str());
    #ifdef DEBUG
        std::cout << lineNumber << "| " << command << ": " << *expression << std::endl; // Debug
    #endif
    delete[] cline;
}








