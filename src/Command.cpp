//
// Created by Szenes Márton on 2024. 04. 12..
//

#include "../include/Command.h"

//Command::Command(const char* cmdStr, void (*funcPtr)(Computer& pc)) : command(cmdStr), func(funcPtr) {}
//
//void Command::operator()(Computer& pc) {
//    func(pc);
//}

bool Command::operator==(const string &str) {
    return command == str;
}

Command::Command(const char *cmdStr, void (*funcPtr)(Computer &, const string &)) : command(cmdStr), func(funcPtr) {}

void Command::operator()(Computer &pc, const string &filename) {
    func(pc, filename);
}


//FileCommand::FileCommand(const char *cmdStr, void (*funcPtr)(Computer &, const string &)) : Command(cmdStr), func(funcPtr) {}
//
//void FileCommand::operator()(Computer &pc, const string &filename) {
//    func(pc, filename);
//}
