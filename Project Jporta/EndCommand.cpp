//
// Created by Marci on 2024. 04. 24..
//
#include "EndCommand.h"
#include "memtrace.h"

EndCommand::EndCommand(Computer &pc) : Command(pc, END_CMD) {}

void EndCommand::operator()(const string &filename, bool &active) { active = false; }