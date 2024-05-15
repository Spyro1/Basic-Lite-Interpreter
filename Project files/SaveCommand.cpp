//
// Created by Marci on 2024. 04. 24..
//

#include <fstream>
#include <iostream>
#include "SaveCommand.h"
#include "memtrace.h"

SaveCommand::SaveCommand(Computer &pc) : Command(pc, SAVE_CMD) {}

void SaveCommand::operator()(const string &filename, bool &active) {
    pc.SaveProgramToFile(filename);
    std::cout << "[Computer]: Program saved to file.\n" << std::endl;

}