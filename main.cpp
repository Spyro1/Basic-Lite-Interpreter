#include <iostream>

//#define CPORTA
//#define MEMTRACE

//#include "memtrace.h"

#include "include/Computer.h"
#include "gtest_lite.h"



#define UTF8

int main() {
    using namespace std;
    #ifdef UTF8
        system("chcp 65001"); // UTF-8 kódolású karakterek használata
    #endif

// === RUN TESTS ===
#ifdef CPORTA
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
    return 0;
}

//