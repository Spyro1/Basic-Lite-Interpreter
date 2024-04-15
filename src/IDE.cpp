//
// Created by Szenes Márton on 2024. 03. 21..
//

#include <iostream>
#include <sstream>
#include <regex>
#include <fstream>
#include "../include/IDE.h"

using std::cin;
using std::cout;
using std::endl;

bool IDE::active = true;

IDE::IDE(std::ostream& out_, std::istream& in_) : out(out_), in(in_) {
    commands.emplace_back(HELP_CMD, HelpCommandFunc);
    commands.emplace_back(RUN_CMD, RunCommandFunc);
    commands.emplace_back(END_CMD, EndCommandFunc);
    commands.emplace_back(LIST_CMD, ListCommandFunc);
    commands.emplace_back(LOAD_CMD, LoadCommandFunc);
    commands.emplace_back(SAVE_CMD, SaveCommandFunc);
    commands.emplace_back(NEW_CMD, NewCommandFunc);
}
void IDE::Run() {
    using namespace std;
    Computer pc;
    // Print Title
    PrintTitle();
    // Run program loop
    while (active){
        cout << "> ";
        // Read line
        string line, commandStr, argumentStr; // Input line
        cin.clear();
        std::getline(cin, line);
        // Split line tot tokens
        std::istringstream iss(line);
        std::getline(iss >> commandStr >> std::ws, argumentStr);
        // Convert command string to upper case for comparing
        commandStr = Computer::ToUpperCaseStr(commandStr);

        try {
            // Iterate through commands
            size_t i = 0;
            while (i < commands.size()){
                if (commands[i] == commandStr) { // check if the command is the inputed one
                    commands[i](pc, argumentStr); // Call command fucntion
                    break;
                }
                i++;
            }
            if (i >= commands.size()){
                if (isNumber(commandStr)){
                    pc.NewInstruction(line); // Add new instruction to computer
                }
                else if (!commandStr.empty()){
                    cout << "[Computer]: Unrecognizable command!" << endl;
                }
            }
        } catch (std::exception& e){
            cout << "\n" << e.what() << endl;
        }
    }
}

// -- Private Functions --

void IDE::PrintTitle() {
    cout << "================================== BASIC-lite ====================================\n"
    <<      "\t\t\t     Made by: Marton Szenes\n"
    <<      "==================================================================================" << endl;
}
bool IDE::isNumber(const std::string& str) {
    size_t i = 0;
    bool hasDigits = false;
    // Check for optional presign
    if (i < str.length() && (str[i] == '+' || str[i] == '-')) { i++; }
    // Check for digits
    while (i < str.length() && std::isdigit(str[i])) {
        hasDigits = true;
        i++;
    }
    return i == str.length() && hasDigits;
}

// -- Functions to commands --

void IDE::HelpCommandFunc(Computer& pc, const string& filename) {
    const string tab = "\t\t\t\t";
    cout << "===================================== HELP =======================================\n"
    << RUN_CMD << tab << "Runs the the program loaded to the memory\n"
    << END_CMD << tab << "Exits the application\n"
    << LIST_CMD << tab << "Displays the instructions of the program in order\n"
    << NEW_CMD << tab << "Creates a new project\n"
    << LOAD_CMD << " <filename>\t\t\tLoads the given program from file if exists\n"
    << SAVE_CMD << " <filename>\t\t\tSaves the opened project with the given file name\n"
    << "<id> <instruction> <parameter>\tAdd new instruction to the program\n"
    << "-<id>" << tab << "Remove instruction by the given line number\n"
    << "==================================================================================\n" << endl;
}
void IDE::RunCommandFunc(Computer& pc, const string& filename) {
    pc.RunProgram();
    cout << "[Computer]: Ready.\n" << endl;
}
void IDE::EndCommandFunc(Computer& pc, const string& filename) {
    active = false;
}
void IDE::ListCommandFunc(Computer& pc, const string& filename) {
    cout << pc;
    cout << "[Computer]: Instructions listed.\n" << endl;
}
void IDE::LoadCommandFunc(Computer& pc, const string& filename) {
    pc.ReadProgramFromFile(filename);
    cout << "[Computer]: Program loaded from file.\n" << endl;
}
void IDE::SaveCommandFunc(Computer& pc, const string& filename){
    std::fstream fileWriter;
    fileWriter.open(filename, std::ios::out);
    if (fileWriter.is_open()){
        fileWriter << pc << endl;
        cout << "[Computer]: Program saved to file.\n" << endl;
    }
    else{
        cout << "[Computer]: Can not save to file.\n" << endl;
    }
    fileWriter.close();
}
void IDE::NewCommandFunc(Computer& pc, const string& filename){
    pc.ClearProgram();
    cout << "[Computer]: New program created.\n" << endl;
}





