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

using std::string;

class IDE {
    bool runIDE;
    string filename;
public:
    // -- Constructors --
    IDE();
    // -- Functions --
    void Run();
    static bool isNumber(const string &str) ;
private:
    // -- Private Functions --
    void PrintHelpCommandList() const;
    void PrintTitle() const;
    void PrintInstructionList() const;
};

#endif //NAGYHAZI_IDE_H
