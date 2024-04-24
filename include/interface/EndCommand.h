//
// Created by Marci on 2024. 04. 24..
//

#ifndef NAGYHAZI_ENDCOMMAND_H
#define NAGYHAZI_ENDCOMMAND_H

#include "Command.h"

class EndCommand : public Command{
public:
    // == Constructor ==
    explicit EndCommand(Computer& pc);
    // == Operator ==
    void operator()(const string& filename, bool& active) override;
};

#endif //NAGYHAZI_ENDCOMMAND_H