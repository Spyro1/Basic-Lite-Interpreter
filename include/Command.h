//
// Created by Szenes Márton on 2024. 04. 12..
//

#ifndef NAGYHAZI_COMMAND_H
#define NAGYHAZI_COMMAND_H

#include <string>

using std::string;

class Command {
    string command;
    void (*func)();
public:
    // -- Constructor --
    /**
     *
     * @param cmdStr
     * @param funcPtr
     */
    Command(const char* cmdStr, void (*funcPtr)());
    // -- Operators --
    /**
     * Calls the Function dedicated to this command
     */
    void operator()();
    /**
     * Checks if the given string is equal to the command
     * @param str command tester string
     * @return equality of the string to the command
     */
    bool operator==(const string& str);
};


#endif //NAGYHAZI_COMMAND_H
