#include <iostream>

#include "memtrace.h"
#include "include/Computer.h"
#include "gtest_lite.h"

#define CPORTA

int main() {
    using namespace std;

#ifdef CPORTA // TEST
    // Lista test



    // Coputer test
    Computer pc;
    TEST(Test1, NemLetezoFajlBeolvas) {
            EXPECT_THROW(pc.ReadProgramFromFile("nincsilyenfajl"), runtime_error&);
    } ENDM
    TEST(Test1, LetezoFajlBeolvas){
            EXPECT_NO_THROW(pc.ReadProgramFromFile("../programs/test.dat")); // Found
    } ENDM








#endif
    // Alapfeladat
//    try {
////        pc.ReadProgramFromFile("program.txt"); // Error
////        pc.ReadProgramFromFile("program1.dat"); // Found
//        pc.RunProgram();
//    }
//    catch (std::exception& e){
//        cout << "Error: " << e.what() << endl;
//    }

    return 0;
}

//