//
// Created by Szenes Márton on 2024. 03. 14..
//
#include <fstream>
#include <iostream>
#include <cstring>
#include <sstream>
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

void Computer::ReadProgramFromFile(const string& filename) {
    using namespace std;
    // If this computer has read a program before, then free dynamic memory from registers and istructions
    DeleteProgramArrays();
    // Read file
    fstream filereader;
    filereader.open(filename,ios::in); // Open file
    // If file doesn't exist, then throw exception
    if (!filereader.is_open()){
        filereader.close();
        throw runtime_error(string("File reading error: '") + filename + string("' file not found!"));
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
void Computer::NewInstruction(const string& programLine) {
    ProcessProgramLine(programLine);
}
void Computer::RunProgram() {
    int counter = 0;
    const int infiniteCycle = 10000;
    while (instructionIndex < instructions.getCount() && counter <= infiniteCycle){
        ExecuteNextInstruction();
        counter++;
    }
    if (counter >= infiniteCycle) throw std::overflow_error(string("Program shutdown: Infinite cycle detected!"));
}

void Computer::ExecuteNextInstruction() {
    instructions[instructionIndex]->Execute(registers,instructions,instructionIndex);
}

void Computer::DeleteProgramArrays() {
    instructions.Clear();
    instructionIndex = -1;
}
Computer::~Computer() {

}
void Computer::ProcessProgramLine(const string& line) {
    int lineNumber = 0;
    string expression;
    string command;

    SplitLineToTokens(line, lineNumber, command, expression);
    if (lineNumber != 0) { // if linenumber is 0, then it is a comment
        if (command == LET) {
            if (lineNumber < 0) instructions.Remove(new LetInstruction(-lineNumber, expression));
            else instructions.Add(new LetInstruction(lineNumber, expression));
        }
        else if (command == PRINT) {
            if (lineNumber < 0) instructions.Remove(new PrintInstruction(-lineNumber, expression));
            else instructions.Add(new PrintInstruction(lineNumber, expression));
        }
        else if (command == IF) {
            if (lineNumber < 0) instructions.Remove(new IfInstruction(-lineNumber, expression));
            else instructions.Add(new IfInstruction(lineNumber, expression));
        }
        else if(command == GOTO) {
            if (lineNumber < 0) instructions.Remove(new GotoInstruction(-lineNumber, expression));
            else instructions.Add(new GotoInstruction(lineNumber, expression));
        }
        else if (command == READ) {
            if (lineNumber < 0) instructions.Remove(new ReadInstruction(-lineNumber, expression));
            else instructions.Add(new ReadInstruction(lineNumber, expression));
        }
        else {
            throw std::logic_error(string("Syntax error: Instruction not recognized in line: ") + std::to_string(lineNumber));
        }
    }
//        else if (command == RUN)
//        instructions.Add(new Instruction())
//    delete[] expression;
}
void Computer::SplitLineToTokens(const string& inputLine, int& lineNumber, string&command, string& expression) {
    std::istringstream iss(inputLine);
    iss >> lineNumber >> command;
    std::getline(iss >> std::ws, expression);


//    using namespace std;
//    // Convert string inputLine to char*
//    char* cline = new char[inputLine.length() + 1];
//    strcpy(cline, inputLine.c_str());
//    int k = 0;
//    // This code snippet is based on this example: https://cplusplus.com/reference/string/string/c_str/
//    char* p = strtok(cline," ");
//    string argument;
//    while (p != nullptr) {
//        if (k == 0) lineNumber = stoi(p); // Extract inputLine number
//        else if (k == 1) command = string(p); // Extract command
//        else if (k > 1) argument += string(p); // Extract argument
//        // std::cout << p << endl;
//        p = strtok(nullptr, " ");
//        k++;
//    }
//    // End of code snippet
//    if (k < 3 && lineNumber != 0) throw runtime_error(string("Syntax error: Not enough arguments in inputLine: ") + to_string(lineNumber));
//    // Convert argument to char* expression
//    expression = argument;
    #ifdef DEBUG
        std::cout << lineNumber << "| " << command << ": " << *expression << std::endl; // Debug
    #endif
//    delete[] cline;
}