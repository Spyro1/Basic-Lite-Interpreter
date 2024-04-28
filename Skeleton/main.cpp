
#define CPORTA

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


int main() {
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

    TEST (Instruction, DrivedClasses){
        vector<Instruction*> instructions; // Instruction list
        vector<Register> registers; // Register list
        int index = 0; // Index of the instruction

        EXPECT_NO_THROW(instructions.push_back(new LetInstruction(10, "a = 4*(4-1)/2 % 4")));
        EXPECT_NO_THROW(instructions.push_back(new GotoInstruction(20, "40")));
        EXPECT_NO_THROW(instructions.push_back(new LetInstruction(30, "a = b = 1")));
        EXPECT_NO_THROW(instructions.push_back(new ReadInstruction(40, "a")));
        EXPECT_NO_THROW(instructions.push_back(new IfInstruction(50, "a > 1 && a <= 3")));
        EXPECT_NO_THROW(instructions.push_back(new PrintInstruction(60, "\"true\"")));
        EXPECT_NO_THROW(instructions.push_back(new PrintInstruction(70, "\"false\"")));
        // Run instructions
        while (instructions[index]->getLineNumber() <= 70){
            EXPECT_NO_THROW(instructions[index]->Execute(registers, instructions, index));
        }
        for (size_t i = 0; i < instructions.size(); ++i) {
            delete instructions[i];
        }
        instructions.clear();
    } END


    // === Computer tests ===
    Computer pc;
    TEST(Computer, ReadNonExistingFile) {
        EXPECT_THROW(pc.ReadProgramFromFile("nincsilyenfajl"), UniqueError); // File not found
    } END
    TEST(Computer, ReadExistingFile){
        EXPECT_NO_THROW(pc.ReadProgramFromFile("program.dat")); // Found
    } END
    TEST(Computer, RunEvenNumberProgram){
        EXPECT_NO_THROW(pc.RunProgram());
    } END
    TEST(Computer, ClearProgram){
        EXPECT_NO_THROW(pc.ClearProgram());
    }END
    TEST(Computer, AddInstruction){
        pc.NewInstruction(string("10 let a = 10"));
        pc.NewInstruction(string("20 let a = (5 - 1) * (a % 6) / 2 + a"));
        pc.NewInstruction(string("30 print a"));
        EXPECT_EQ(3, (int)pc.getInstructionCount());
        EXPECT_NO_THROW(pc.RunProgram());
    }END
    TEST(Computer, RemoveInstruction){
        pc.NewInstruction(string("-20"));
        EXPECT_EQ(2, (int)pc.getInstructionCount());
        EXPECT_NO_THROW(pc.RunProgram());
    }END

    TEST(Interface, CreateIDE){
        IDE ide;
    }END

    if (!gtest_lite::test.fail())
        std::cout << "\nAll test have been called.\nThe application works!" << std::endl;

#else
    std::cout << "Nem futottak a tesztek, mert CPORTA nincs definialva." << std::endl;
#endif

    return 0;
}
