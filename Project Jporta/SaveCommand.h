//
// Created by Marci on 2024. 04. 24..
//

#ifndef NAGYHAZI_SAVECOMMAND_H
#define NAGYHAZI_SAVECOMMAND_H

#include "Command.h"

/**
 * The SaveCommand class represents a command to save the program to a file.
 * Inherits from the Command class.
 */
class SaveCommand : public Command {
public:
    // == Constructor ==
    /**
     * Constructs a SaveCommand object.
     * @param pc A reference to the Computer object.
     */
    explicit SaveCommand(Computer& pc);
    // == Operator ==
    /**
     * Executes the Save command.
     * @param filename The name of the file to save the program to.
     * @param active A boolean reference indicating whether the interface is active.
     */
    void operator()(const std::string& filename, bool& active) override;
};



#endif //NAGYHAZI_SAVECOMMAND_H
