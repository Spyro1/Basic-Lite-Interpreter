//
// Created by Marci on 2024. 04. 24..
//

#include <fstream>
#include <iostream>
#include "SaveCommand.h"
#include "memtrace.h"

SaveCommand::SaveCommand(Computer &pc) : Command(pc, SAVE_CMD) {}

void SaveCommand::operator()(const string &filename, bool &active) {
    std::fstream fileWriter;
    fileWriter.open(filename, std::ios::out);
    if (fileWriter.is_open()){
        fileWriter << pc << std::endl;
        std::cout << "[Computer]: Program saved to file.\n" << std::endl;
    }
    else{
        std::cout << "[Computer]: Can not save to file.\n" << std::endl;
    }
    fileWriter.close();
}