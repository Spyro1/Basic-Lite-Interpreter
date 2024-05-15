//
// Created by Marci on 2024. 04. 24..
//

#include <iostream>
#include "LoadCommand.h"
#include "memtrace.h"

LoadCommand::LoadCommand(Computer &pc) : Command(pc, LOAD_CMD) {}

void LoadCommand::operator()(const string &filename, bool &active) {
    pc.ReadProgramFromFile(filename);
    std::cout << "[Computer]: Program loaded from file.\n" << std::endl;
}