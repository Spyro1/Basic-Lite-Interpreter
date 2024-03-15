cmake_minimum_required(VERSION 3.27)
project(Nagyhazi)

set(CMAKE_CXX_STANDARD 11)

add_executable(Nagyhazi main.cpp
        Computer.h Computer.cpp
        Register.h Register.cpp
        Instruction.h Instruction.cpp
        PrintInstruction.h PrintInstruction.cpp
        LetInstruction.h LetInstruction.cpp
        List.h
)

target_compile_options(Nagyhazi PRIVATE -Wall -Werror)