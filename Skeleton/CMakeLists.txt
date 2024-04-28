cmake_minimum_required(VERSION 3.28)
project(Skeleton)

set(CMAKE_CXX_STANDARD 11)

add_executable(Skeleton main.cpp
gtest_lite.h
IDE.h
Computer.h
Register.h
Instruction.h
GotoInstruction.h
IfInstruction.h
LetInstruction.h
PrintInstruction.h
ReadInstruction.h

Command.h
HelpCommand.h
RunCommand.h
EndCommand.h
ListCommand.h
NewCommand.h
LoadCommand.h
SaveCommand.h

CompileError.h
SyntaxError.h
UniqueError.h)

