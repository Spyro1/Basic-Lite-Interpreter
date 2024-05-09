cmake_minimum_required(VERSION 3.26)
project(Nagyhazi)

set(CMAKE_CXX_STANDARD 11)

add_executable(Nagyhazi main.cpp
        gtest_lite.h
        memtrace.h
        memtrace.cpp
        SyntaxError.h
        UniqueError.h
        IDE.h IDE.cpp
        Command.h Command.cpp
        Computer.h Computer.cpp
        Register.h Register.cpp
        Instruction.h Instruction.cpp
        PrintInstruction.h PrintInstruction.cpp
        LetInstruction.h LetInstruction.cpp
        IfInstruction.h IfInstruction.cpp
        GotoInstruction.h GotoInstruction.cpp
        ReadInstruction.h ReadInstruction.cpp
        HelpCommand.h HelpCommand.cpp
        RunCommand.h RunCommand.cpp
        EndCommand.h EndCommand.cpp
        ListCommand.h ListCommand.cpp
        NewCommand.h NewCommand.cpp
        LoadCommand.h LoadCommand.cpp
        SaveCommand.h SaveCommand.cpp

)
add_compile_definitions(MEMTRACE)
#add_compile_definitions(CPORTA)
target_compile_options(Nagyhazi PRIVATE -Wall -Werror)
