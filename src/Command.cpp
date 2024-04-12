//
// Created by Szenes Márton on 2024. 04. 12..
//

#include "../include/Command.h"

Command::Command(const char* cmdStr, void (*funcPtr)()) : command(cmdStr), func(funcPtr) {}

void Command::operator()() {
    func();
}

bool Command::operator==(const string &str) {
    return command == str;
}


