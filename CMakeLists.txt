cmake_minimum_required(VERSION 3.26)
project(Nagyhazi)

set(CMAKE_CXX_STANDARD 11)

add_executable(Nagyhazi main.cpp
        memtrace.cpp
        memtrace.h
        gtest_lite.h
        include/compiler/Computer.h src/compiler/Computer.cpp
        include/compiler/Register.h src/compiler/Register.cpp
        include/compiler/Instruction.h src/compiler/Instruction.cpp
        include/compiler/PrintInstruction.h src/compiler/PrintInstruction.cpp
        include/compiler/LetInstruction.h src/compiler/LetInstruction.cpp
        include/compiler/IfInstruction.h src/compiler/IfInstruction.cpp
        include/compiler/GotoInstruction.h src/compiler/GotoInstruction.cpp
        include/compiler/ReadInstruction.h src/compiler/ReadInstruction.cpp
        include/IDE.h               src/IDE.cpp
        include/Command.h           src/Command.cpp
        include/exceptions/SyntaxError.h
        include/exceptions/CompileError.h
        include/exceptions/UniqueError.h

)
add_compile_definitions(MEMTRACE)
target_compile_options(Nagyhazi PRIVATE -Wall -Werror)
