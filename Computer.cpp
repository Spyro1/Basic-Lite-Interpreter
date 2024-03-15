//
// Created by Szenes Márton on 2024. 03. 14..
//
#include <fstream>
#include "Computer.h"


Computer::Computer(size_t registerCount) {
    if (registerCount <  2) throw "Error: There are not enough registers for the computer to work."; // Computer can not work with less than 2 registers. (PLAN)
    // Adding default registers
    registers.Add(new Register("a")); // Base register
    registers.Add(new Register("i")); // Counter

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
        throw "Error: File not found!";
    }
    // File was opened
    std::string line;
    char command[10];
    int i = 0;
    while (std::getline(filereader, line)){
//        filereader >> command;
        i++;
    }

    // TODO: Make file reading line by line

    filereader.close();
}
void Computer::RunProgram() {

}

void Computer::ExecuteNextInstruction() {

}

void Computer::DeleteProgramArrays() {

}
Computer::~Computer() {
    DeleteProgramArrays();
}




