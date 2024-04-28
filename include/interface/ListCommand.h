//
// Created by Marci on 2024. 04. 24..
//

#ifndef NAGYHAZI_LISTCOMMAND_H
#define NAGYHAZI_LISTCOMMAND_H

#include "Command.h"

/**
 * The ListCommand class represents a command that lists the instructions of the loaded program.
 * Inherits from the Command class.
 */
class ListCommand : public Command{
public:
    // == Constructor ==
    /**
     * Constructs a ListCommand object.
     * @param pc A reference to the Computer object.
     */
    explicit ListCommand(Computer& pc);
    // == Operator ==
    /**
    * Executes the List command.
    * @param filename The name of the file. (Unused)
    * @param active A boolean reference indicating whether the interface is active.
    */
    void operator()(const string& filename, bool& active) override;
};


#endif //NAGYHAZI_LISTCOMMAND_H
