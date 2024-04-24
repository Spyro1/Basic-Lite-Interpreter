//
// Created by Szenes Márton on 2024. 03. 21..
//

#ifndef NAGYHAZI_IDE_H
#define NAGYHAZI_IDE_H


#include <string>
#include "../compiler/Computer.h"
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
    // Stream references
    std::ostream& out;
    std::istream& in;

    std::vector<Command*> commands;

public:
    // == Constructors ==
    explicit IDE(std::ostream& out = std::cout, std::istream& in = std::cin);
    // == Public Functions ==
    void Run();
    // == Destructor ==
    ~IDE();
private:
    // == Private Functions ==
    static void PrintTitle();
    // == Functions to commands ==
//    static void HelpCommandFunc(Computer& pc, const string& filename);
//    static void RunCommandFunc(Computer& pc, const string& filename);
//    static void EndCommandFunc(Computer& pc, const string& filename);
//    static void ListCommandFunc(Computer& pc, const string& filename);
//    static void LoadCommandFunc(Computer& pc, const string& filename);
//    static void SaveCommandFunc(Computer& pc, const string& filename);
//    static void NewCommandFunc(Computer& pc, const string& filename);
};

#endif //NAGYHAZI_IDE_H
