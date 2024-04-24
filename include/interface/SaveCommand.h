//
// Created by Marci on 2024. 04. 24..
//

#ifndef NAGYHAZI_SAVECOMMAND_H
#define NAGYHAZI_SAVECOMMAND_H

#include "Command.h"

class SaveCommand : public Command{
public:
    // == Constructor ==
    explicit SaveCommand(Computer& pc);
    // == Operator ==
    void operator()(const string& filename, bool& active) override;
};


#endif //NAGYHAZI_SAVECOMMAND_H
