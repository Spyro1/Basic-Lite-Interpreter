//
// Created by Szenes Márton on 2024. 03. 14..
//
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "Computer.h"
#include "memtrace.h"

// == Constructor ==
Computer::Computer() {
    // Clear instructions array
    ClearInstructions();
    // Clear register array
    registers.clear();
}

// == Getters ==
size_t Computer::getInstructionCount() const {
    return instructions.size();
}

// == Functions ==
void Computer::ReadProgramFromFile(const string& filename) {
    using namespace std;
    // If this computer has read a program before, then free dynamic memory from registers and instructions
    ClearInstructions();
    // File reader
    fstream filereader;
    filereader.open(filename,ios::in); // Open file
    // If file doesn't exist, then throw exception
    if (!filereader.is_open()){
        filereader.close();
        throw UniqueError('\"' + filename + "\" file not found!");
    }
    // File opened, read in file:
    string line;
    while (std::getline(filereader, line, '\n')) {
        ProcessProgramLine(line);
    }
    filereader.close(); // Close File
    instructionIndex = 0; // Set instruction index to the beginning
    // Make instruction in order based on the line number
    SortInstructions();
}

void Computer::NewInstruction(const string& programLine) {
    instructionIndex = 0; // Set instruction index to the beginning
    ProcessProgramLine(programLine); // Processing the new instruction
    SortInstructions(); // Make instruction in order based on the line number
}

void Computer::RunProgram() {
    int counter = 0;
    instructionIndex = 0; // Set instruction index to the beginning
    const int infiniteCycle = 10000;
    registers.clear();
    while ((size_t)instructionIndex < instructions.size() && counter <= infiniteCycle){
        instructions[instructionIndex]->Execute(registers,instructions,instructionIndex); // Execute next instruction
        counter++;
    }
    if (counter >= infiniteCycle) throw CompileError("Program shutdown due to infinite cycle!");
    #ifndef CPORTA
        std::cout << std::endl;
    #endif
}

void Computer::ClearProgram() {
    registers.clear();
    ClearInstructions();
}

std::ostream &operator<<(std::ostream &os, const Computer &pc) {
//    os << "[Computer]: Number of instructions: " << pc.instructions.size() << "\n";
    for (auto instruction : pc.instructions) {
        os << *instruction << "\n";
    }
    return os;
}

string Computer::ToUpperCaseStr(const string& str) {
    string result;
    for (char ch : str) {
        result += (char)toupper(ch);
    }
    return result;
}

// == Private functions ==
void Computer::ProcessProgramLine(const string& line) {
    // Output vars
    int lineNumber = 0;
    string expression, command;
    // Split to tokens
    SplitLineToTokens(line, lineNumber, command, expression);
    // Test if line identifier already exists
    if (std::any_of(instructions.begin(), instructions.end(),[&lineNumber](Instruction* inst) { return inst->getLineNumber() == lineNumber; })){
        throw SyntaxError("Line identifier already exists: " + std::to_string(lineNumber));
    }
    // Remove instruction line if it is a negative number
    if (lineNumber < 0) RemoveInstruction(-lineNumber);
    else if (lineNumber != 0) { // If linenumber is 0, then it is a comment
        command = ToUpperCaseStr(command);
        if (command == LET)
            instructions.push_back(new LetInstruction(lineNumber, expression));
        else if (command == PRINT)
            instructions.push_back(new PrintInstruction(lineNumber, expression));
        else if (command == IF)
            instructions.push_back(new IfInstruction(lineNumber, expression));
        else if(command == GOTO)
            instructions.push_back(new GotoInstruction(lineNumber, expression));
        else if (command == READ)
            instructions.push_back(new ReadInstruction(lineNumber, expression));
        else
            throw SyntaxError("Instruction not recognized", lineNumber ); // Instruction not recognized
    }
}

void Computer::SplitLineToTokens(const string& inputLine, int& lineNumber, string&command, string& expression) {
    std::istringstream iss(inputLine);
    iss >> lineNumber >> command;
    std::getline(iss >> std::ws, expression);
}

void Computer::ClearInstructions() {
    for (auto& instruction : instructions) {
        delete instruction;
    }
    instructions.clear();
    instructionIndex = -1;
}

void Computer::SortInstructions() {
    std::sort(instructions.begin(), instructions.end(), CompareInstructions);
}

void Computer::RemoveInstruction(int lineNumber){
    for (auto it = instructions.begin(); it != instructions.end(); ++it) {
        if ((*it)->getLineNumber() == lineNumber) { // Replace getField() with the appropriate field and desiredValue with the value to match
            // Remove the object from the vector
            delete *it;
            instructions.erase(it);
            break;
        }
    }
}

bool Computer::CompareInstructions(const Instruction* a, const Instruction* b) {
    return a->getLineNumber() < b->getLineNumber();
}

// == Destructor ==
Computer::~Computer() {
    ClearInstructions();
}