#include <iostream>

#include "memtrace.h"
#include "include/Computer.h"
#include "gtest_lite.h"

//#define CPORTA

int main() {
    using namespace std;

// === RUN TESTS ===
#ifdef CPORTA
    // List test
    TEST (List, FunctionTesting){
        List<Register> testRegisters;
        EXPECT_EQ(0, testRegisters.getCount());                                     // Empty list count is 0
        testRegisters.Add(new Register("reg1"));
        testRegisters.Add(new Register("reg2", 10));
        testRegisters.Add(new Register("reg3", 5));
        EXPECT_EQ(3, testRegisters.getCount());                                     // Added 3 items -> count = 3
        EXPECT_EQ(0, testRegisters[0]->getValue());                                 // Test getter and default value
        EXPECT_EQ(10, testRegisters[1]->getValue());                                // Test getter with given value
        EXPECT_STREQ("reg1", testRegisters[0]->getName().c_str());                          // Test name getter
        testRegisters.Sort();                                                       // Sorting list based of < and > operators declared in type class
        EXPECT_EQ(5, testRegisters[1]->getValue());                                 // After sortig the second item should be "reg3" with value 5
        EXPECT_FALSE(testRegisters.Remove(new Register("reg4")));  // No such register named "reg3"
        EXPECT_TRUE(testRegisters.Remove(new Register("reg1")));   // Deleting register named "reg1"
        EXPECT_EQ(2, testRegisters.getCount());                                     // 2 item remaining in the list
        testRegisters.Clear();                                                      // Removing all items from the list
        EXPECT_EQ(0, testRegisters.getCount());                                     // 0 items remaining in the list
    } END
    // Coputer test
    Computer pc;
    TEST(Test1, NemLetezoFajlBeolvas) {
        EXPECT_THROW(pc.ReadProgramFromFile("nincsilyenfajl"), runtime_error&); // File not found
    } END
    TEST(Test1, LetezoFajlBeolvas){
        EXPECT_NO_THROW(pc.ReadProgramFromFile("../programs/test.dat")); // Found
        pc.RunProgram();
    } END

#endif

// === RUN PROGRAM INTERFACE ===
#ifndef CPORTA
    try{
        Computer pc;
        pc.ReadProgramFromFile("../programs/test.dat");
        pc.RunProgram();
    }
    catch (std::exception& e){
        cout << e.what() << endl;
    }
#endif


    // Vektor minta:
//    std::vector<Register> inst;
//
//    // Add new Register to the list
//    Register reg1( "Register1");
//    Register reg2( "Register2");
//    inst.push_back(reg1);
//    inst.push_back(reg2);
//    std::string nameToRemove = "Register1";
//    auto it = std::remove_if(inst.begin(), inst.end(), [nameToRemove](const Register& reg) {
//        return reg.getName() == nameToRemove;
//    });
//    inst.erase(it, inst.end());
//    for (const auto& reg : inst) {
//        std::cout << "Name: " << reg.getName() << ", Value: " << reg.getValue() << std::endl;
//    }
    return 0;
}

//