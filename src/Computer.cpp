//
// Created by Szenes Márton on 2024. 03. 14..
//
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "../include/Computer.h"
#include "../include/LetInstruction.h"
#include "../include/PrintInstruction.h"
#include "../include/IfInstruction.h"
#include "../include/GotoInstruction.h"
#include "../include/ReadInstruction.h"


Computer::Computer() {
    // Clear instructions
    ClearInstructions();
    // Adding default registers
    registers.clear();
}

void Computer::ReadProgramFromFile(const string& filename) {
    using namespace std;
    // If this computer has read a program before, then free dynamic memory from registers and istructions
    ClearInstructions();
    // Read file
    fstream filereader;
    filereader.open(filename,ios::in); // Open file
    // If file doesn't exist, then throw exception
    if (!filereader.is_open()){
        filereader.close();
        throw runtime_error(string("[Error]: \"") + filename + string("\" file not found!"));
    }
    // File opened, read in file:
    string line;
    while (std::getline(filereader, line, '\n')) {
        ProcessProgramLine(line);
    }

    filereader.close(); // Close File
    instructionIndex = 0;
    // Make instruction in order based on the line number
    SortInstructions();
    #ifdef DEBUG
        cout << "First line test cout: " << *instructions[0] << endl;
    #endif
}
void Computer::NewInstruction(const string& programLine) {
    instructionIndex = 0;
    ProcessProgramLine(programLine);
    SortInstructions();
}
void Computer::RunProgram() {
    int counter = 0;
    const int infiniteCycle = 10000;
    instructionIndex = 0;
    while ((size_t)instructionIndex < instructions.size() && counter <= infiniteCycle){
        ExecuteNextInstruction();
        counter++;
    }
    if (counter >= infiniteCycle) throw std::runtime_error(string("[Runtime error]: Program shutdown due to infinite cycle!"));
    std::cout << std::endl;
}

void Computer::ExecuteNextInstruction() {
    try{
        // Execute the next line's instruction
        instructions[instructionIndex]->Execute(registers,instructions,instructionIndex);
    } catch (std::exception& e){
        // Throw error if something passed the error check and it can't compile
        throw std::runtime_error(string("[Error]: Unknown error (") + e.what() + string(") in line: ") + std::to_string(instructions[instructionIndex]->getLineNumber()));
    }

}

Computer::~Computer() {
    ClearInstructions();
}
void Computer::ProcessProgramLine(const string& line) {
    // Output vars
    int lineNumber = 0;
    string expression;
    string command;
    // Spolit to tokens
    SplitLineToTokens(line, lineNumber, command, expression);
    // Test if line identifier already exists
    if (std::any_of(instructions.begin(), instructions.end(),[&lineNumber](Instruction* inst) { return inst->getLineNumber() == lineNumber; })){
        throw std::runtime_error(string("[Syntax error]: Line indentifier already exists: ") + std::to_string(lineNumber));
    }
    // Remove instruction line if it is a negative number
    if (lineNumber < 0) RemoveInstruction(-lineNumber);
    else if (lineNumber != 0) { // If linenumber is 0, then it is a comment
        command = ToUpperCaseStr(command);
        if (command == LET) {
            instructions.push_back(new LetInstruction(lineNumber, expression));
        }
        else if (command == PRINT) {
            instructions.push_back(new PrintInstruction(lineNumber, expression));
        }
        else if (command == IF) {
            instructions.push_back(new IfInstruction(lineNumber, expression));
        }
        else if(command == GOTO) {
            instructions.push_back(new GotoInstruction(lineNumber, expression));
        }
        else if (command == READ) {
            instructions.push_back(new ReadInstruction(lineNumber, expression));
        }
        else {
            // Instruction not recognized
            throw std::logic_error(string("[Syntax error]: Instruction not recognized in line: ") + std::to_string(lineNumber));
        }
    }
}
void Computer::SplitLineToTokens(const string& inputLine, int& lineNumber, string&command, string& expression) {
    std::istringstream iss(inputLine);
    iss >> lineNumber >> command;
    std::getline(iss >> std::ws, expression);
    #ifdef DEBUG
        std::cout << "Tokens: "<< lineNumber << "| " << command << " | " << expression << std::endl; // Debug
    #endif
}
void Computer::ClearInstructions() {
    for (size_t i = 0; i < instructions.size(); ++i) {
        delete instructions[i];
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
string Computer::ToUpperCaseStr(const string& str) {
    string result;
    for (char ch : str) {
        result += toupper(ch);
    }
    return result;
}
std::ostream &operator<<(std::ostream &os, const Computer &pc) {
//    os << "[Computer]: Number of instructions: " << pc.instructions.size() << "\n";
    for (auto instruction : pc.instructions) {
        os << *instruction << "\n";
    }
    return os;
}
size_t Computer::getInstructionCount() const {
    return instructions.size();
}

void Computer::ClearProgram() {
    registers.clear();
    ClearInstructions();
}


