cmake_minimum_required(VERSION 3.26)
project(Nagyhazi)

set(CMAKE_CXX_STANDARD 11)

add_executable(Nagyhazi main.cpp
        memtrace.cpp
        memtrace.h
        gtest_lite.h
        include/Computer.h          src/Computer.cpp
        include/Register.h          src/Register.cpp
        include/Instruction.h       src/Instruction.cpp
        include/PrintInstruction.h  src/PrintInstruction.cpp
        include/LetInstruction.h    src/LetInstruction.cpp
        include/IfInstruction.h     src/IfInstruction.cpp
        include/GotoInstruction.h   src/GotoInstruction.cpp
        include/ReadInstruction.h   src/ReadInstruction.cpp
        include/IDE.h src/IDE.cpp
        include/Command.h
)
add_compile_definitions(MEMTRACE)
target_compile_options(Nagyhazi PRIVATE -Wall -Werror)
