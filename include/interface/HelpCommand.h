//
// Created by Marci on 2024. 04. 24..
//

#ifndef NAGYHAZI_HELPCOMMAND_H
#define NAGYHAZI_HELPCOMMAND_H

#include "Command.h"

class HelpCommand : public Command{
public:
    // == Constructor ==
    explicit HelpCommand(Computer& pc);
    // == Operator ==
    void operator()(const string& filename, bool& active) override;
};


#endif //NAGYHAZI_HELPCOMMAND_H
