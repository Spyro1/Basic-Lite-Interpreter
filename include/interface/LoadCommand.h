//
// Created by Marci on 2024. 04. 24..
//

#ifndef NAGYHAZI_LOADCOMMAND_H
#define NAGYHAZI_LOADCOMMAND_H

#include "Command.h"

class LoadCommand : public Command{
public:
    // == Constructor ==
    explicit LoadCommand(Computer& pc);
    // == Operator ==
    void operator()(const string& filename, bool& active) override;
};


#endif //NAGYHAZI_LOADCOMMAND_H
