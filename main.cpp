#include <iostream>

#define CPORTA

#include "memtrace.h"
#include "include/LetInstruction.h"
#include "include/PrintInstruction.h"
#include "include/GotoInstruction.h"
#include "include/ReadInstruction.h"
#include "include/IfInstruction.h"
#include "include/Computer.h"
#include "include/IDE.h"
#include "gtest_lite.h"



//#define UTF8

int main() {
    using namespace std;
    #ifdef UTF8
        system("chcp 65001"); // Set character encoding to UTF-8
    #endif

// === RUN TESTS ===
#ifdef CPORTA

    // Register tests
    TEST(Register, DefConstructor){
        Register reg;
        EXPECT_FLOAT_EQ(.0f, reg.getValue());
        EXPECT_STREQ("", reg.getName().c_str());
    } END
    TEST(Register, ParamConstructor){
        Register reg("a", 11.3);
        EXPECT_FLOAT_EQ(11.3f, reg.getValue());
        EXPECT_STREQ("a", reg.getName().c_str());
        reg.SetValue((float)2/3);
        EXPECT_FLOAT_EQ((float)2/3, reg.getValue());
    } END

    // Instruction tests
    TEST(Instruction, Getters) {
        Instruction* instr = new PrintInstruction(10, "\"kiirat\"");
        EXPECT_STREQ("\"kiirat\"", instr->getExpression().c_str());
        EXPECT_EQ(10, instr->getLineNumber());
        EXPECT_EQ(InstructionType::Print, instr->getInstructionType());
        EXPECT_STREQ(PRINT, instr->getInstructionTypeStr().c_str());
        delete instr;
    } END

    vector<Instruction*> instructions; // Instruction list
    vector<Register> registers; // Register list
    int index = 0;

    TEST (Instruciton, PrintInstruction_Correct){
        EXPECT_NO_THROW(instructions.push_back(new PrintInstruction(10, "\"helyes kiiras\"")));
        EXPECT_NO_THROW(instructions[index]->Execute(registers, instructions, index));
    } END

    TEST (Instruction, PrintInstruction_Error){
        index = 1; // Set back
        EXPECT_NO_THROW(instructions.push_back(new PrintInstruction(20, "\"rossz")));
        // [Syntax error]: Wrong string literal in line: #
        EXPECT_THROW(instructions[index]->Execute(registers, instructions, index), exception& e);
        instructions.pop_back(); // Pop from array
        index = 1; // Set back
        EXPECT_NO_THROW(instructions.push_back(new PrintInstruction(20, "valami")));
        // [Syntax error]: Can not recognize "argument" as a print argument in line: #
        EXPECT_THROW(instructions[index]->Execute(registers, instructions, index), exception& e);
        instructions.pop_back(); // Pop from array
    } END

    TEST (Instruction, LetInstruction_Correct){
        index = 1;
        EXPECT_NO_THROW(instructions.push_back(new LetInstruction(20, "a = 4*(4-1)/2")));
        EXPECT_NO_THROW(instructions[index]->Execute(registers, instructions, index));
        EXPECT_EQ(6.f, registers[0].getValue());
    } END

    TEST(Instruction, LetInstruction_Error){
        index = 2;
        EXPECT_NO_THROW(instructions.push_back(new LetInstruction(20, "a = 4*(4-b)/2")));
        // [Syntax error]: Uninitialized register used in line: #
        EXPECT_THROW(instructions[index]->Execute(registers, instructions, index), exception&);
        instructions.pop_back();
    } END
//        EXPECT_NO_THROW(instructions.push_back(new LetInstruction(20, "a = 1")));
//        EXPECT_NO_THROW(instructions.push_back(new IfInstruction(30, "a==1")));
//                instructions.push_back(new PrintInstruction(10, "\"kiirat\""));
//        instructions.push_back(new PrintInstruction(10, "\"kiirat\""));
//        EXPECT_NO_THROW(instructions[index]->Execute(registers, instructions, index));


//        EXPECT_FLOAT_EQ(1.f, registers[0].getValue());

    // Coputer tests
    Computer pc;
    TEST(ComputerTest1, ReadNonExistingFile) {
        EXPECT_THROW(pc.ReadProgramFromFile("nincsilyenfajl"), runtime_error&); // File not found
    } END
    TEST(ComputerTest2, ReadExistingFile){
        EXPECT_NO_THROW(pc.ReadProgramFromFile("../programs/parosSzamok.dat")); // Found
    } END
    TEST(ComputerTest3, RunEvenNumberProgram){
        EXPECT_NO_THROW(pc.RunProgram());
    } END
    TEST(ComputerTest4, ClearProgram){
        EXPECT_NO_THROW(pc.ClearProgram());
    }END
    TEST(ComputerTest5, AddInstruction){
        pc.NewInstruction(string("10 let a = 10"));
        pc.NewInstruction(string("20 let a = (5 - 1) * (a % 6) / 2 + a"));
        pc.NewInstruction(string("30 print a"));
        EXPECT_EQ(3, (int)pc.getInstructionCount());
        EXPECT_NO_THROW(pc.RunProgram());
    }END
    TEST(ComputerTest6, RemoveInstruction){
        pc.NewInstruction(string("-20"));
        EXPECT_EQ(2, (int)pc.getInstructionCount());
        EXPECT_NO_THROW(pc.RunProgram());
    }END

    TEST(InterfaceTest1, CreateIDE){
        IDE ide;
    }END
    IDE ide;
//    TEST(InterfaceTest2, RunIDE){
//        EXPECT_NO_THROW(ide.Run()) << "Ennek nem igy kene mukodnie";
//    }END

    if (!gtest_lite::test.fail())
      std::cout << "\nMinden teszt lefutott.\nA program tokeletesen mukodik!" << std::endl;
    string str;
    std::cin >> str;
#endif

// === RUN PROGRAM INTERFACE ===
#ifndef CPORTA
    try{
        IDE ide;
        ide.Run();
    }
    catch (std::exception& e){
        cout << "\n[Error]: Undetected error in interface: " << e.what() << endl;
    }
#endif
    return 0;
}


// TODO: Ötletek: Függvényhívás implemetálás