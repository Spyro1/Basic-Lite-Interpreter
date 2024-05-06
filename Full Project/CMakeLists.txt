cmake_minimum_required(VERSION 3.26)
project(Nagyhazi)

set(CMAKE_CXX_STANDARD 11)

add_executable(Nagyhazi main.cpp
        gtest_lite.h
        memtrace.h                          memtrace.cpp
        include/exceptions/SyntaxError.h
        include/exceptions/CompileError.h
        include/exceptions/UniqueError.h
        include/interface/IDE.h             src/interface/IDE.cpp
        include/interface/Command.h         src/interface/Command.cpp
        include/compiler/Computer.h         src/compiler/Computer.cpp
        include/compiler/Register.h         src/compiler/Register.cpp
        include/compiler/Instruction.h      src/compiler/Instruction.cpp
        include/compiler/PrintInstruction.h src/compiler/PrintInstruction.cpp
        include/compiler/LetInstruction.h   src/compiler/LetInstruction.cpp
        include/compiler/IfInstruction.h    src/compiler/IfInstruction.cpp
        include/compiler/GotoInstruction.h  src/compiler/GotoInstruction.cpp
        include/compiler/ReadInstruction.h  src/compiler/ReadInstruction.cpp
        include/interface/HelpCommand.h     src/interface/HelpCommand.cpp
        include/interface/RunCommand.h      src/interface/RunCommand.cpp
        include/interface/EndCommand.h      src/interface/EndCommand.cpp
        include/interface/ListCommand.h     src/interface/ListCommand.cpp
        include/interface/NewCommand.h      src/interface/NewCommand.cpp
        include/interface/LoadCommand.h     src/interface/LoadCommand.cpp
        include/interface/SaveCommand.h     src/interface/SaveCommand.cpp

)
add_compile_definitions(MEMTRACE)
#add_compile_definitions(CPORTA)
target_compile_options(Nagyhazi PRIVATE -Wall -Werror)
