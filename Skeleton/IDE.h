//
// Created by Szenes Márton on 2024. 03. 21..
//

#ifndef NAGYHAZI_IDE_H
#define NAGYHAZI_IDE_H


#include <string>
#include "Computer.h"
#include "Command.h"
#include "HelpCommand.h"
#include "RunCommand.h"
#include "EndCommand.h"
#include "ListCommand.h"
#include "NewCommand.h"
#include "LoadCommand.h"
#include "SaveCommand.h"

using std::string;

class IDE {
    bool active = true;
    Computer pc;
    std::vector<Command*> commands;

public:
    // == Constructors ==
    explicit IDE();
    // == Public Functions ==
    void Run();
    // == Destructor ==
    ~IDE();
};

#endif //NAGYHAZI_IDE_H
