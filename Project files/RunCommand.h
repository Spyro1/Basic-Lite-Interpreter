//
// Created by Marci on 2024. 04. 24..
//

#ifndef NAGYHAZI_RUNCOMMAND_H
#define NAGYHAZI_RUNCOMMAND_H

#include "Command.h"

/**
 * The RunCommand class represents a command to run the program on the interpreter.
 * Inherits from the Command class.
 */
class RunCommand : public Command {
public:

    // == Constructor ==
    /**
     * Constructs a RunCommand object.
     * @param pc A reference to the Computer object.
     */
    explicit RunCommand(Computer& pc);

    // == Operator ==
    /**
     * Executes the Run command.
     * @param filename The name of the file to be executed on.
     * @param active A boolean reference indicating whether the interface is active.
     */
    void operator()(const string& filename, bool& active) override;
};


#endif //NAGYHAZI_RUNCOMMAND_H
