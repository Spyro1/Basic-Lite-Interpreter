//
// Created by Szenes Márton on 2024. 03. 21..
//

#ifndef NAGYHAZI_IDE_H
#define NAGYHAZI_IDE_H

#include <string>
#include "Computer.h"
#include "Command.h"


using std::string;

/**
 * Represents an Integrated Development Environment (IDE) for the user to interact with.
 */
class IDE {
    bool active = true;             // Flag indicating whether the IDE is active or not.
    Computer pc;                    // Interpreter for the program.
    std::vector<Command*> commands; // Vector containing pointers to Command objects.

public:

    // == Constructors ==
    /**
    * Constructs an IDE object, initializes the IDE with default commands.
    */
    IDE();

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
private:
    // == Private Functions ==
    /**
     * Prints the title to console.
     */
    static void PrintTitle();
    /**
     * Reads a line from the console
     * @param line Reference to a string representing the whole inputted line by the user.
     * @param commandStr Reference to a string containing the command keyword extracted from the line.
     * @param argumentStr Reference to a string containing the argument of the instruction.
     */
    void ReadInput(string &line, string &commandStr, string &argumentStr);
};

#endif //NAGYHAZI_IDE_H
