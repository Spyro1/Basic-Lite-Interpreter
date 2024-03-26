//
// Created by Szenes Márton on 2024. 03. 21..
//

#include <iostream>
#include <sstream>
#include <regex>
#include "../include/IDE.h"
#include "../include/Computer.h"

using std::cin;
using std::cout;
using std::endl;

IDE::IDE() {

}
void IDE::Run() {
    using namespace std;
    runIDE = true;
    Computer pc;
    string line, commandStr, argumentStr;
    // Print TITLE
    PrintTitle();
    // Run program loop
    while (runIDE){
        cout << "> ";
        // Read line
        std::getline(cin, line);
        // Split line tot tokens
        std::istringstream iss(line);
        std::getline(iss >> commandStr >> std::ws, argumentStr);
        // Convert command string to upper case for comparing
        commandStr = Computer::ToUpperCaseStr(commandStr);
        try {
            if (commandStr == HELP_CMD){
                PrintHelpCommandList();
            }
            else if (commandStr == RUN_CMD){
                pc.RunProgram();
            }
            else if (commandStr == END_CMD){
                runIDE = false;
            }
            else if (commandStr == LIST_CMD){
                cout << pc << endl;
            }
            else if (commandStr == NEW_CMD){
                cout << "New program created";
            }
            else if (commandStr == LOAD_CMD){
                cout << "Program loaded from file";
            }
            else if (commandStr == SAVE_CMD){
                cout << "Program saved to file";
            }
            else if (isNumber(commandStr)){
                // Add new instruction to computer
                pc.NewInstruction(line);
            }
            else if (!commandStr.empty()){
                cout << "[Computer]: Unrecognizable command!" << endl;
            }
        } catch (std::exception& e){
            cout << "\n" << e.what() << endl;
        }

    }
}
void IDE::PrintTitle() const {
    cout << "================================== BASIC-lite ====================================\n"
    <<      "\t\t\t     Made by: Szenes Marton\n"
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
void IDE::PrintInstructionList() const {

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
