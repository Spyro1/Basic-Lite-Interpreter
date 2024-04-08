//
// Created by Szenes Márton on 2024. 03. 21..
//

#include <iostream>
#include <sstream>
#include <regex>
#include <fstream>
#include "../include/IDE.h"
#include "../include/Computer.h"

using std::cin;
using std::cout;
using std::endl;

IDE::IDE() : runIDE(true) { }
void IDE::Run() {
    using namespace std;
    Computer pc; // Computer of the program
    // Print Title
    PrintTitle();
    // Run program loop
    while (runIDE){
        cout << "> ";
        // Read line
        string line, commandStr, argumentStr; // Input line
        cin.clear();
        std::getline(cin, line);
//        cin >> line;
//        cout << cin.good() ;

        // Split line tot tokens
        std::istringstream iss(line);
        std::getline(iss >> commandStr >> std::ws, argumentStr);
//        std::getline(cin >> commandStr >> std::ws, argumentStr);

        // Convert command string to upper case for comparing
        commandStr = Computer::ToUpperCaseStr(commandStr);
        try {
            if (commandStr == HELP_CMD){
                PrintHelpCommandList();
            }
            else if (commandStr == RUN_CMD){
                pc.RunProgram();
                cout << "[Computer]: Ready." << endl;
            }
            else if (commandStr == END_CMD){
                runIDE = false;
            }
            else if (commandStr == LIST_CMD){
                cout << pc << endl;
            }
            else if (commandStr == NEW_CMD){
                NewProgramProject(pc);
            }
            else if (commandStr == LOAD_CMD){
                LoadProgramFile(pc, argumentStr);
            }
            else if (commandStr == SAVE_CMD){
                SaveProgramFile(pc, argumentStr);
            }
            else if (isNumber(commandStr)){
                // Add new instruction to computer
                pc.NewInstruction(line);
            }
            else if (!commandStr.empty()){
                cout << "[Computer]: Unrecognizable command!" << endl;
            }
        } catch (std::exception& e){
            cout/* << "\n"*/ << e.what() << endl;
        }

    }
}
void IDE::PrintTitle() const {
    cout << "================================== BASIC-lite ====================================\n"
    <<      "\t\t\t     Made by: Marton Szenes\n"
    <<      "==================================================================================" << endl;
}
void IDE::PrintHelpCommandList() const {
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
    << "==================================================================================" << endl;
}
void IDE::LoadProgramFile(Computer& pc, const string& file) {
    pc.ReadProgramFromFile(file);
    cout << "[Computer]: Program loaded from file." << endl;
}
void IDE::SaveProgramFile(Computer& pc, const string& file){
    std::fstream fileWriter;
    fileWriter.open(file, std::ios::out);
    if (fileWriter.is_open()){
        fileWriter << pc << endl;
        cout << "[Computer]: Program saved to file." << endl;
    }
    else{
        cout << "[Computer]: Can not save to file." << endl;
    }
    fileWriter.close();
}
void IDE::NewProgramProject(Computer& pc){
    pc.ClearProgram();
    cout << "[Computer]: New program created." << endl;
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
