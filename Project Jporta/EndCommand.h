//
// Created by Marci on 2024. 04. 24..
//

#ifndef NAGYHAZI_ENDCOMMAND_H
#define NAGYHAZI_ENDCOMMAND_H

#include "Command.h"

/**
 * The EndCommand class represents a command that closes the interface upon executed.
 * Inherits from the Command class.
 */
class EndCommand : public Command {
public:

    // == Constructor ==
    /**
     * Constructs a EndCommand object.
     * @param pc A reference to the Computer object.
     */
    explicit EndCommand(Computer& pc);

    // == Operator ==
    /**
    * Executes the End command.
    * @param filename The name of the file. (Unused)
    * @param active A boolean reference indicating whether the interface is active.
    */
    void operator()(const string& filename, bool& active) override;
};

#endif //NAGYHAZI_ENDCOMMAND_H