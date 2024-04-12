//
// Created by Szenes Márton on 2024. 04. 12..
//

#include "../include/Command.h"

Command::Command(const char* cmdStr, void (*funcPtr)(Computer& pc, const string& filename)) : command(cmdStr), func(funcPtr) {}

void Command::operator()(Computer& pc, const string& filename) {
    func(pc, filename);
}

bool Command::operator==(const string &str) {
    return command == str;
}


