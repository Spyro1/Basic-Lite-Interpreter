//
// Created by Marci on 2024. 04. 24..
//

#ifndef NAGYHAZI_NEWCOMMAND_H
#define NAGYHAZI_NEWCOMMAND_H

#include "Command.h"

class NewCommand : public Command{
public:
    // == Constructor ==
    explicit NewCommand(Computer& pc);
    // == Operator ==
    void operator()(const string& filename, bool& active) override;
};


#endif //NAGYHAZI_NEWCOMMAND_H
