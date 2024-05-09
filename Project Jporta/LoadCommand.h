//
// Created by Marci on 2024. 04. 24..
//

#ifndef NAGYHAZI_LOADCOMMAND_H
#define NAGYHAZI_LOADCOMMAND_H

#include "Command.h"

/**
 * The LoadCommand class represents a command to load the program from a file.
 * Inherits from the Command class.
 */
class LoadCommand : public Command{
public:
    // == Constructor ==
    /**
     * Constructs a LoadCommand object.
     * @param pc A reference to the Computer object.
     */
    explicit LoadCommand(Computer& pc);
    // == Operator ==
    /**
     * Executes the Load command.
     * @param filename The name of the file to load the program from.
     * @param active A boolean reference indicating whether the interface is active.
     */
    void operator()(const string& filename, bool& active) override;
};


#endif //NAGYHAZI_LOADCOMMAND_H
