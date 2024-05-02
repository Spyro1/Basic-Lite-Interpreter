//
// Created by Szenes Márton on 2024. 04. 12..
//

#include "../../include/interface/Command.h"

Command::Command(Computer &pc, const char *cmdStr) : pc(pc), cmdStr(cmdStr) {}

bool Command::operator==(const string &commandStr) {
    return cmdStr == commandStr;
}