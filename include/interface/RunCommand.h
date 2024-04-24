//
// Created by Marci on 2024. 04. 24..
//

#ifndef NAGYHAZI_RUNCOMMAND_H
#define NAGYHAZI_RUNCOMMAND_H

#include "Command.h"

class RunCommand : public Command{
public:
    // == Constructor ==
    explicit RunCommand(Computer& pc);
    // == Operator ==
    void operator()(const string& filename, bool& active) override;
};


#endif //NAGYHAZI_RUNCOMMAND_H
