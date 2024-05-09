//
// Created by Marci on 2024. 04. 24..
//

#ifndef NAGYHAZI_HELPCOMMAND_H
#define NAGYHAZI_HELPCOMMAND_H

#include "Command.h"

/**
 * The HelpCommand class represents a command that prints the possible commands to the standard output.
 * Inherits from the Command class.
 */
class HelpCommand : public Command{
public:
    // == Constructor ==
    /**
     * Constructs a HelpCommand object.
     * @param pc A reference to the Computer object.
     */
    explicit HelpCommand(Computer& pc);
    // == Operator ==
    /**
    * Executes the Help command.
    * @param filename The name of the file. (Unused)
    * @param active A boolean reference indicating whether the interface is active.
    */
    void operator()(const string& filename, bool& active) override;
};


#endif //NAGYHAZI_HELPCOMMAND_H
