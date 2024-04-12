//
// Created by Szenes Márton on 2024. 03. 21..
//

#ifndef NAGYHAZI_IDE_H
#define NAGYHAZI_IDE_H

#define HELP_CMD "HELP"
#define RUN_CMD "RUN"
#define END_CMD "END"
#define LIST_CMD "LIST"
#define NEW_CMD "NEW"
#define LOAD_CMD "LOAD"
#define SAVE_CMD "SAVE"

#include <string>
#include "Computer.h"
#include "Command.h"

using std::string;


class IDE {
    static bool active;
    Computer pc; // Computer of the program
//    string filename;
    std::vector<Command> commands;
public:
    // -- Constructors --
    IDE();
    // -- Functions --
    void Run();
private:
    // -- Private Functions --
    bool isNumber(const string &str);
    // -- Finctions to commands --
    void PrintTitle();
    static void HelpCommandFunc(Computer& pc, const string& filename);
    static void RunCommandFunc(Computer& pc, const string& filename);
    static void EndCommandFunc(Computer& pc, const string& filename);
    static void ListCommandFunc(Computer& pc, const string& filename);
    static void LoadCommandFunc(Computer& pc, const string& filename);
    static void SaveCommandFunc(Computer& pc, const string& filename);
    static void NewCommandFunc(Computer& pc, const string& filename);
};

#endif //NAGYHAZI_IDE_H
