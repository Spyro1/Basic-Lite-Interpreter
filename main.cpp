#include <iostream>

//#define CPORTA

#include "memtrace.h"
#include "gtest_lite.h"
#include "include/IDE.h"
#include "include/compiler/Computer.h"
#include "include/compiler/PrintInstruction.h"
#include "include/compiler/LetInstruction.h"
#include "include/compiler/GotoInstruction.h"
#include "include/compiler/ReadInstruction.h"
#include "include/compiler/IfInstruction.h"



//#define UTF8

int main() {
    using namespace std;
    #ifdef UTF8
        system("chcp 65001"); // Set character encoding to UTF-8
    #endif

// === RUN TESTS ===
#ifdef CPORTA

    // === Register tests ===
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

    // === Instruction tests ===
    TEST(Instruction, Getters) {
        Instruction* instr = new PrintInstruction(10, "\"kiirat\"");
        EXPECT_STREQ("\"kiirat\"", instr->getExpression().c_str());
        EXPECT_EQ(10, instr->getLineNumber());
        EXPECT_EQ(InstructionType::Print, instr->getInstructionType());
        EXPECT_STREQ(PRINT, instr->getInstructionTypeStr().c_str());
        delete instr;
    } END

    // === Instruction types tests ===
    vector<Instruction*> instructions; // Instruction list
    vector<Register> registers; // Register list
    int index; // Index of the instruction

    TEST (PrintInstruction, Correct){
        index = 0; // Set to first
        // Print string literal
        EXPECT_NO_THROW(instructions.push_back(new PrintInstruction(10, "\"helyes kiiras\"")));
        EXPECT_NO_THROW(instructions[index]->Execute(registers, instructions, index));
        instructions.pop_back(); // Pop from array
    } END

    TEST (PrintInstruction, Error){
        index = 0; // Set back
        // [Syntax error]: Wrong string literal in line: #
        EXPECT_NO_THROW(instructions.push_back(new PrintInstruction(10, "\"rossz")));
        EXPECT_THROW(instructions[index]->Execute(registers, instructions, index), exception& e);

        // [Syntax error]: Can not recognize "argument" as a print argument in line: #
        EXPECT_NO_THROW(instructions.push_back(new PrintInstruction(10, "valami")));
        EXPECT_THROW(instructions[index]->Execute(registers, instructions, index), exception& e);
        instructions.clear(); // Clear array
    } END

    TEST (LetInstruction, Correct){
        index = 0;
        // Set value with all existing operations
        EXPECT_NO_THROW(instructions.push_back(new LetInstruction(10, "a = 4*(4-1)/2 % 4")));
        EXPECT_NO_THROW(instructions[index]->Execute(registers, instructions, index));
        EXPECT_EQ(2.f, registers[0].getValue());
        // Chained assigning
        EXPECT_NO_THROW(instructions.push_back(new LetInstruction(10, "a = b = 1")));
        EXPECT_NO_THROW(instructions[index]->Execute(registers, instructions, index));
        EXPECT_EQ(1.f, registers[0].getValue());
        EXPECT_EQ(1.f, registers[1].getValue());
        instructions.clear(); // Clear array
    } END

    TEST(LetInstruction, Error){
        index = 0;
        // [Syntax error]: Unrecognized register name in line: #
        EXPECT_NO_THROW(instructions.push_back(new LetInstruction(40, "a = c")));
        EXPECT_THROW(instructions[index]->Execute(registers, instructions, index), exception&);
//        instructions.pop_back();
    } END

    TEST(GotoInstruction, Correct){
        index = 4;
        EXPECT_NO_THROW(instructions.push_back(new GotoInstruction(50, "40")));
        EXPECT_NO_THROW(instructions[index]->Execute(registers, instructions, index));
        // Last test's error again after goto back to line 40
        EXPECT_THROW(instructions[index]->Execute(registers, instructions, index), exception&);
    } END

    TEST(GotoInstruction, Error){

    } END

    TEST(ReadInstruction, Correct){

    } END
    TEST (ReadInstruction, Error){

    } END

    TEST(IfInstruction, Correct){

    } END
    TEST (IfInstruction, Error){

    } END

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
      std::cout << "\n\tMinden teszt lefutott.\n\tA program tokeletesen mukodik!" << std::endl;
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

// DONE: NOT operátor implementálása

// DONE: Goto argument lehessen expression és register érték is

// TODO: Custom Syntax Error exception class implementation

// TODO: IfInstruction tesztek írása

// TODO: ReadInstruction tesztek írása

// TODO: Command class kibővítése leszármazottakkal (RunCommand, HelpCommand, ... )

// TODO: IDE-ből eltávolítani a static függvényeket

// TODO: Függvénydokumentáció írás:
//  - Computer
//  - Instruction leszármazottak
//      - IfInstruction
//      - ReadInstruction
//      - LetInstruction
//      - PrintInstruction
//      - GotoInstruction
//  - IDE