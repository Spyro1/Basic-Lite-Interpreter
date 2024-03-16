cmake_minimum_required(VERSION 3.26)
project(Nagyhazi)

set(CMAKE_CXX_STANDARD 11)

add_executable(Nagyhazi main.cpp
        List.h
        Computer.h          Computer.cpp
        Register.h          Register.cpp
        Instruction.h       Instruction.cpp
        PrintInstruction.h  PrintInstruction.cpp
        LetInstruction.h    LetInstruction.cpp
        IfInstruction.h     IfInstruction.cpp
        GotoInstruction.h   GotoInstruction.cpp
        ReadInstruction.h   ReadInstruction.cpp
)

target_compile_options(Nagyhazi PRIVATE -Wall -Werror)