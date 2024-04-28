//
// Created by Marci on 2024. 04. 24..
//

#include <iostream>
#include "../../include/interface/HelpCommand.h"

HelpCommand::HelpCommand(Computer &pc) : Command(pc, HELP_CMD) { }

void HelpCommand::operator()(const string &filename, bool &active) {
    const string tab = "\t\t\t\t";
    std::cout << "===================================== HELP =======================================\n"
         << RUN_CMD << tab << "Runs the the program loaded to the memory\n"
         << END_CMD << tab << "Exits the application\n"
         << LIST_CMD << tab << "Displays the instructions of the program in order\n"
         << NEW_CMD << tab << "Creates a new project\n"
         << LOAD_CMD << " <filename>\t\t\tLoads the given program from file if exists\n"
         << SAVE_CMD << " <filename>\t\t\tSaves the opened project with the given file name\n"
         << "<id> <instruction> <parameter>\tAdd new instruction to the program\n"
         << "-<id>" << tab << "Remove instruction by the given line number\n"
         << "==================================================================================\n" << std::endl;
}
