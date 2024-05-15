//
// Created by Szenes Márton on 2024. 04. 12..
//
#include "Command.h"
#include "memtrace.h"

Command::Command(Computer &pc, const char *cmdStr) : pc(pc), cmdStr(cmdStr) {}

bool Command::operator==(const string &commandStr) {
    return cmdStr == commandStr;
}