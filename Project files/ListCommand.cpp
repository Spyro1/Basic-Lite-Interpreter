//
// Created by Marci on 2024. 04. 24..
//

#include <iostream>
#include "ListCommand.h"
#include "memtrace.h"

ListCommand::ListCommand(Computer &pc) : Command(pc, LIST_CMD) {}

void ListCommand::operator()(const string &filename, bool &active) {
    std::cout << pc << "[Computer]: Instructions listed.\n" << std::endl;
}