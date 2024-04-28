//
// Created by Szenes Márton on 2024. 03. 21..
//

#include <iostream>
#include <sstream>
#include <regex>
#include <fstream>
#include "../../include/interface/IDE.h"


using std::cin;
using std::cout;
using std::endl;


IDE::IDE(std::ostream& out_, std::istream& in_) : out(out_), in(in_) {
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

    // Print Title
    PrintTitle();
    // Run program loop
    while (active){
        cout << "> ";
        // Read line
        string line, commandStr, argumentStr; // Input line
        cin.clear();
        std::getline(cin, line);
        // Split line to tokens
        std::istringstream iss(line);
        std::getline(iss >> commandStr >> std::ws, argumentStr);
        // Convert command string to upper case for comparing
        commandStr = Computer::ToUpperCaseStr(commandStr);

        try {
            // Iterate through commands
            size_t i = 0;
            while (i < commands.size()){
                if (*commands[i] == commandStr) { // check if the command is the inputed one
                    (*commands[i])(argumentStr, active); // Call command fucntion
                    break;
                }
                i++;
            }
            if (i >= commands.size()){
                if (Instruction::isNumber(commandStr)){
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

IDE::~IDE() {
    for (size_t i = 0; i < commands.size(); ++i) {
        delete commands[i];
    }
}





