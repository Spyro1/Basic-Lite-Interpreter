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
    bool active = true;             /// Flag indicating whether the IDE is active or not.
    Computer pc;                    /// Interpreter for the program.
    std::vector<Command*> commands; /// Vector containing pointers to Command objects.

public:
    // == Constructors ==
    /**
    * Constructs an IDE object, initializes the IDE with default commands.
    */
    explicit IDE();
    // == Public Functions ==
    /**
     * This function runs the IDE on the terminal, allowing users to interact with it.
     */
    void Run();
    // == Destructor ==
    /**
    * Destroys the IDE object, cleans up resources allocated by the IDE.
    */
    ~IDE();
};

#endif //NAGYHAZI_IDE_H
