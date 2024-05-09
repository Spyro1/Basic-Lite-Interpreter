//#define CPORTA
//#define UTF8

#include <iostream>
#include "gtest_lite.h"
#include "IDE.h"
#include "Computer.h"

#ifdef CPORTA
#include "PrintInstruction.h"
#include "LetInstruction.h"
#include "GotoInstruction.h"
#include "ReadInstruction.h"
#include "IfInstruction.h"
#endif
#include "memtrace.h"



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
        EXPECT_NO_THROW(instructions.push_back(new PrintInstruction(10, "\"output success\"")));
            stringbuf test_output(ios_base::out);
            streambuf * const cout_buf = cout.rdbuf(&test_output);
        EXPECT_NO_THROW(instructions[index]->Execute(registers, instructions, index));
            cout.rdbuf(cout_buf);
        EXPECT_STREQ("output success", test_output.str().c_str()); // Test output content
        delete instructions[0];
        instructions.pop_back(); // Pop from array
    } END

    TEST (PrintInstruction, Error){
        index = 0; // Set back
        // [Syntax error]: Wrong string literal in line: #
        EXPECT_NO_THROW(instructions.push_back(new PrintInstruction(10, "\"wrong")));
        EXPECT_THROW(instructions[index]->Execute(registers, instructions, index), SyntaxError);

        // [Syntax error]: Can not recognize "argument" as a print argument in line: #
        EXPECT_NO_THROW(instructions.push_back(new PrintInstruction(10, "something")));
        EXPECT_THROW(instructions[index]->Execute(registers, instructions, index), SyntaxError);
        delete instructions[0];
        delete instructions[1];
        instructions.clear(); // Clear array
    } END

    TEST (LetInstruction, Correct){
        index = 0;
        // Set value with all existing operations
        EXPECT_NO_THROW(instructions.push_back(new LetInstruction(20, "a = 4*(4-1)/2 % 4")));
        EXPECT_NO_THROW(instructions[index]->Execute(registers, instructions, index));
        EXPECT_EQ(2.f, registers[0].getValue());
        // Chained assigning
        EXPECT_NO_THROW(instructions.push_back(new LetInstruction(20, "a = b = 1")));
        EXPECT_NO_THROW(instructions[index]->Execute(registers, instructions, index));
        EXPECT_EQ(1.f, registers[0].getValue());
        EXPECT_EQ(1.f, registers[1].getValue());
        delete instructions[0];
        delete instructions[1];
        instructions.clear(); // Clear array
        registers.clear(); // Clear array
    } END

    TEST(LetInstruction, Error){
        index = 0;
        // [Syntax error]: Unrecognized register name in line: #
        EXPECT_NO_THROW(instructions.push_back(new LetInstruction(20, "a = c")));
        EXPECT_THROW(instructions[index]->Execute(registers, instructions, index), SyntaxError);
        delete instructions[0];
        instructions.pop_back();
    } END

    TEST(GotoInstruction, Correct){
        index = 0;
        EXPECT_NO_THROW(instructions.push_back(new GotoInstruction(30, "30")));
        EXPECT_NO_THROW(instructions[index]->Execute(registers, instructions, index));
        delete instructions[0];
        instructions.pop_back();
    } END

    TEST(GotoInstruction, Error){
        index = 0;
        EXPECT_NO_THROW(instructions.push_back(new GotoInstruction(30, "somewhere")));
        EXPECT_THROW(instructions[index]->Execute(registers, instructions, index), SyntaxError);
        EXPECT_NO_THROW(instructions.push_back(new GotoInstruction(40, "")));
        EXPECT_THROW(instructions[index]->Execute(registers, instructions, index), SyntaxError);
        delete instructions[0];
        delete instructions[1];
        instructions.clear();
    } END

    TEST(ReadInstruction, Correct){
        index = 0;
        EXPECT_NO_THROW(instructions.push_back(new ReadInstruction(50, "a")));
            stringbuf test_input("3", ios_base::in); // Set cin input stringbuffer
            streambuf * const cin_buf = cin.rdbuf(&test_input); // Save cin buffer
        EXPECT_NO_THROW(instructions[index]->Execute(registers, instructions, index));
            cin.rdbuf(cin_buf); // Reset cin buffer
        EXPECT_EQ(3.f, registers[0].getValue());
        delete instructions[0];
        instructions.pop_back();
    } END

    TEST (ReadInstruction, Error){
        index = 0;
        EXPECT_NO_THROW(instructions.push_back(new ReadInstruction(50, "a")));
            stringbuf test_input("novalue", ios_base::in); // Set cin input stringbuffer
            streambuf * const cin_buf = cin.rdbuf(&test_input); // Save cin buffer
        EXPECT_THROW(instructions[index]->Execute(registers, instructions, index), UniqueError);
            cin.rdbuf(cin_buf); // Reset cin buffer
        delete instructions[0];
        instructions.pop_back();
    } END

    TEST(IfInstruction, Correct){
        index = 0;
        EXPECT_NO_THROW(instructions.push_back(new IfInstruction(10, "a > 1 && a <= 3")));
        EXPECT_NO_THROW(instructions.push_back(new PrintInstruction(20, "\"true\"")));
        EXPECT_NO_THROW(instructions.push_back(new PrintInstruction(30, "\"false\"")));
            stringbuf test_output(ios_base::out);
            streambuf * const cout_buf = cout.rdbuf(&test_output);
        EXPECT_NO_THROW(instructions[index]->Execute(registers, instructions, index));
            cout.rdbuf(cout_buf);
        EXPECT_STREQ("true", test_output.str().c_str());
        delete instructions[0];
        delete instructions[1];
        delete instructions[2];
        instructions.clear();
    } END
    TEST (IfInstruction, Error){
        index = 0;
        EXPECT_NO_THROW(instructions.push_back(new IfInstruction(10, "a >| 1 &")));
        EXPECT_THROW(instructions[index]->Execute(registers, instructions, index), SyntaxError);
        delete instructions[0];
        instructions.clear();
    } END

    // === Computer tests ===
    Computer pc;
    TEST(Computer, ReadNonExistingFile) {
        EXPECT_THROW(pc.ReadProgramFromFile("nincsilyenfajl"), UniqueError); // File not found
    } END
    TEST(Computer, ReadExistingFile){
        EXPECT_NO_THROW(pc.ReadProgramFromFile("parosSzamok.dat")); // Found
    } END
    TEST(Computer, RunEvenNumberProgram){
            stringbuf test_output(ios_base::out); // Set up test output
            streambuf * const cout_buf = cout.rdbuf(&test_output); // Store cout buffer
        EXPECT_NO_THROW(pc.RunProgram());
            cout.rdbuf(cout_buf); // Reset cout buffer
        EXPECT_STREQ("Elso 5 paros szam: 2 4 6 8 10 ", test_output.str().c_str()); // Test cout result
    } END
    TEST(Computer, ClearProgram){
        EXPECT_NO_THROW(pc.ClearProgram());
    }END
    TEST(Computer, AddInstruction){
        pc.NewInstruction(string("10 let a = 10"));
        pc.NewInstruction(string("20 let a = (5 - 1) * (a % 6) / 2 + a"));
        pc.NewInstruction(string("30 print a"));
        EXPECT_EQ(3, (int)pc.getInstructionCount());
            stringbuf test_output(ios_base::out); // Set up test output
            streambuf * const cout_buf = cout.rdbuf(&test_output); // Store cout buffer
        EXPECT_NO_THROW(pc.RunProgram());
            cout.rdbuf(cout_buf); // Reset cout buffer
        EXPECT_STREQ("18", test_output.str().c_str());
    }END
    TEST(Computer, RemoveInstruction){
        pc.NewInstruction(string("-20"));
        EXPECT_EQ(2, (int)pc.getInstructionCount());
            stringbuf test_output(ios_base::out); // Set up test output
            streambuf * const cout_buf = cout.rdbuf(&test_output); // Store cout buffer
        EXPECT_NO_THROW(pc.RunProgram());
            cout.rdbuf(cout_buf); // Reset cout buffer
        EXPECT_STREQ("10", test_output.str().c_str());
    }END

    TEST(Interface, CreateIDE){
        IDE ide;
    }END
    TEST(Interface, RunIDE){
        IDE ide;
        stringbuf test_input("10 LET a = 4 + 2\n20 PRINT a\nRUN\nEND", ios_base::in); // Set cin input stringbuffer
        streambuf * const cin_buf = cin.rdbuf(&test_input); // Save cin buffer
        stringbuf test_output(ios_base::out); // Redirect cout
        streambuf * const cout_buf = cout.rdbuf(&test_output); // Save cout buffer
        EXPECT_NO_THROW(ide.Run()) << "Error during IDE test.";
        cin.rdbuf(cin_buf); // Reset cin buffer
        cout.rdbuf(cout_buf); // Reset cout buffer
    }END
    TEST(Interface, LoadFile){
        IDE ide;
        stringbuf test_input("LOAD factorial.dat\nRUN\n5\nEND", ios_base::in); // Set cin input stringbuffer
        streambuf * const cin_buf = cin.rdbuf(&test_input); // Save cin buffer
        stringbuf test_output(ios_base::out); // Redirect cout
        streambuf * const cout_buf = cout.rdbuf(&test_output); // Save cout buffer
        EXPECT_NO_THROW(ide.Run()) << "Error during IDE test.";
        cin.rdbuf(cin_buf); // Reset cin buffer
        cout.rdbuf(cout_buf); // Reset cout buffer
    }END

    if (!gtest_lite::test.fail())
      std::cout << "\nAll test have been called.\nThe application works!" << std::endl;

#endif

// === RUN PROGRAM INTERFACE ===
#ifndef CPORTA
    try{
        IDE ide;
        ide.Run();
    }
    catch (std::exception& e){
        cout << "\n[Error]: Undetected error in interface: " << e.what() << endl;
        string a;
        getline(cin,a);
    }
#endif
    return 0;
}

// DONE: NOT operátor implementálása

// DONE: Goto argument lehessen expression és register érték is

// DONE: Custom Syntax Error exception class implementation

// DONE: IfInstruction tesztek írása

// DONE: ReadInstruction tesztek írása

// DONE: Command class kibővítése leszármazottakkal (RunCommand, HelpCommand, ... )

// DONE: IDE-ből eltávolítani a static függvényeket

// TODO: Függvénydokumentáció írás:
//  + Computer
//  + Instruction leszármazottak
//      + IfInstruction
//      + ReadInstruction
//      + LetInstruction
//      + PrintInstruction
//      + GotoInstruction
//  - IDE
//  - HelpCommand
//  - EndCommand