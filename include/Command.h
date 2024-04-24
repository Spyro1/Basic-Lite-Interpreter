//
// Created by Szenes Márton on 2024. 04. 12..
//

#ifndef NAGYHAZI_COMMAND_H
#define NAGYHAZI_COMMAND_H

#include <string>
#include "compiler/Computer.h"

using std::string;

class Command {
    string cmdStr;
    void (*func)(Computer& pc, const string& filename);
public:
    // -- Constructor --
    /**
     * Creates a command that the user can use from the IDE
     * @param cmdStr String literal fo the command
     * @param funcPtr This function is called, when the command is inputed
     */
    explicit Command(const char* cmdStr,  void (*funcPtr)(Computer& pc, const string& filename) = nullptr);
    // -- Operators --
    /**
     * Calls the Function dedicated to this command
     */
    void operator()(Computer& pc, const string& filename);
    /**
     * Checks if the given string is equal to the command
     * @param str command tester string
     * @return equality of the string to the command
     */
    bool operator==(const string& str);
};

#endif //NAGYHAZI_COMMAND_H
