//
// Created by Szenes Márton on 2024. 03. 21..
//

#include <iostream>
#include <sstream>
#include <regex>
#include "../../memtrace.h"
#include "../../include/interface/IDE.h"


using std::cin;
using std::cout;
using std::endl;


IDE::IDE() {
    // Add base commands to interface
    commands.push_back(new HelpCommand(pc));
    commands.push_back(new RunCommand(pc));
    commands.push_back(new EndCommand(pc));
    commands.push_back(new ListCommand(pc));
    commands.push_back(new NewCommand(pc));
    commands.push_back(new LoadCommand(pc));
    commands.push_back(new SaveCommand(pc));
}
void IDE::Run() {
    using namespace std;

    PrintTitle(); // Print Title to console
    // Run program loop
    while (active){
        cout << "> ";
        // Read line
        string line, commandStr, argumentStr; // Input line
        ReadInput(line, commandStr, argumentStr);
        try {
            // Iterate through commands
            size_t i = 0;
            while (i < commands.size()){
                if (*commands[i] == commandStr) { // check if the command is the inputted one
                    (*commands[i])(argumentStr, active); // Call command function
                    break;
                }
                i++;
            }
            // New instruction inputted
            if (i >= commands.size()){
                if (Instruction::isNumber(commandStr)){
                    pc.NewInstruction(line); // Add new instruction to computer
                }
                // Not empty line inputted
                else if (!commandStr.empty()){
                    cout << "[Computer]: Unrecognizable command!" << endl;
                }
            }
        } catch (std::exception& e){
            cout << "\n" << e.what() << endl;
        }
    }
}

// == Private Functions ==

void IDE::PrintTitle() {
    cout << "================================== BASIC-lite ====================================\n"
    <<      "\t\t\t     Made by: Marton Szenes\n"
    <<      "==================================================================================\n"
    <<      "[Computer]: Type HELP for commands." << endl;
}
void IDE::ReadInput(std::string& line, std::string& commandStr, std::string& argumentStr){
    cin.clear();
    std::getline(cin, line);
    // Split line to tokens
    std::istringstream iss(line);
    std::getline(iss >> commandStr >> std::ws, argumentStr);
    // Convert command string to upper case for comparing
    commandStr = Computer::ToUpperCaseStr(commandStr);
}

// == Destructor ==
IDE::~IDE() {
    for (size_t i = 0; i < commands.size(); ++i) {
        delete commands[i];
    }
}





