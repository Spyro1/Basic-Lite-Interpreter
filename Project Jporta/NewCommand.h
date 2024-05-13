//
// Created by Marci on 2024. 04. 24..
//

#ifndef NAGYHAZI_NEWCOMMAND_H
#define NAGYHAZI_NEWCOMMAND_H

#include "Command.h"

/**
 * The NewCommand represents a command to create a new project.
 * Inherits from the Command class.
 */
class NewCommand : public Command {
public:

    // == Constructor ==
    /**
     * Constructs a NewCommand object.
     * @param pc A reference to the Computer object.
     */
    explicit NewCommand(Computer& pc);

    // == Operator ==
    /**
     * Executes the New command.
     * @param filename The name of the file. (Unused)
     * @param active A boolean reference indicating whether the interface is active.
     */
    void operator()(const string& filename, bool& active) override;
};


#endif //NAGYHAZI_NEWCOMMAND_H
