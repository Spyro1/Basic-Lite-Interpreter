//
// Created by Szenes Márton on 2024. 04. 12..
//

#include "../../include/interface/Command.h"

bool Command::operator==(const string &commandStr) {
    return cmdStr == commandStr;
}

Command::Command(Computer &pc, const char *cmdStr) : pc(pc), cmdStr(cmdStr) {

}
