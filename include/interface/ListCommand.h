//
// Created by Marci on 2024. 04. 24..
//

#ifndef NAGYHAZI_LISTCOMMAND_H
#define NAGYHAZI_LISTCOMMAND_H

#include "Command.h"

class ListCommand : public Command{
public:
    // == Constructor ==
    explicit ListCommand(Computer& pc);
    // == Operator ==
    void operator()(const string& filename, bool& active) override;
};


#endif //NAGYHAZI_LISTCOMMAND_H
