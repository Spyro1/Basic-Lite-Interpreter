#include <iostream>

//#define CPORTA
//#define MEMTRACE

#include "memtrace.h"

#include "include/Computer.h"
#include "include/IDE.h"
#include "gtest_lite.h"



#define UTF8

int main() {
    using namespace std;
    #ifdef UTF8
        system("chcp 65001"); // Set character encoding to UTF-8
    #endif

// === RUN TESTS ===
#ifdef CPORTA
    // Coputer test
    Computer pc;
    TEST(Test1, NemLetezoFajlBeolvas) {
        EXPECT_THROW(pc.ReadProgramFromFile("nincsilyenfajl"), runtime_error&); // File not found
    } END
    TEST(Test2, LetezoFajlBeolvas){
        EXPECT_NO_THROW(pc.ReadProgramFromFile("../programs/parosSzamok.dat")); // Found
    } END
    TEST(Test3, ParosSzamokProgramFuttatas){
        pc.RunProgram();
    } END
#endif

// === RUN PROGRAM INTERFACE ===
#ifndef CPORTA
    try{
//        Computer pc;
//        pc.ReadProgramFromFile("../programs/test.dat");
//        pc.RunProgram();
        IDE ide;
        ide.Run();
    }
    catch (std::exception& e){
        cout << "\n\n" << e.what() << endl;
    }
#endif
    return 0;
}

//