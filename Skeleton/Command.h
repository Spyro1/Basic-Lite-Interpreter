//
// Created by Szenes Márton on 2024. 04. 12..
//

#ifndef NAGYHAZI_COMMAND_H
#define NAGYHAZI_COMMAND_H

#define HELP_CMD "HELP"
#define RUN_CMD "RUN"
#define END_CMD "END"
#define LIST_CMD "LIST"
#define NEW_CMD "NEW"
#define LOAD_CMD "LOAD"
#define SAVE_CMD "SAVE"

#include <string>
#include "Computer.h"

using std::string;

class Command {
protected:
    Computer& pc;
    string cmdStr;
public:
    // == Constructor ==
    /**
     * Creates a command that the user can use from the IDE
     * @param pc Reference to the computer compiling the code
     * @param cmdStr String literal fo the command
     */
    explicit Command(Computer& pc, const char* cmdStr = "");

    // == Operators ==
    /**
     * Calls the Function dedicated to this command
     */
    virtual void operator()(const string& filename, bool& active) = 0;
    /**
     * Checks if the given string is equal to the command
     * @param str command tester string
     * @return equality of the string to the command
     */
    bool operator==(const string& commandStr);

    // == Destructor ==
    virtual ~Command() = default;
};

#endif //NAGYHAZI_COMMAND_H
