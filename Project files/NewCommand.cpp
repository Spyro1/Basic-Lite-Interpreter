//
// Created by Marci on 2024. 04. 24..
//

#include <iostream>
#include "NewCommand.h"
#include "memtrace.h"

NewCommand::NewCommand(Computer &pc) : Command(pc, NEW_CMD) {}

void NewCommand::operator()(const string &filename, bool &active) {
    pc.ClearProgram();
    std::cout << "[Computer]: New program created.\n" << std::endl;
}