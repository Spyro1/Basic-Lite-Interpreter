//
// Created by Marci on 2024. 04. 24..
//

#include <iostream>
#include "RunCommand.h"
#include "memtrace.h"

RunCommand::RunCommand(Computer &pc) : Command(pc, RUN_CMD) {}

void RunCommand::operator()(const string &filename, bool &active) {
    pc.RunProgram();
    std::cout << "\n[Computer]: Ready.\n" << std::endl;
}