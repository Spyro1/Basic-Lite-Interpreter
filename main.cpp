#include <iostream>
#include "include/Computer.h"

int main() {
    using namespace std;
    // Alapfeladat
    try {
        Computer pc;
//        pc.ReadProgramFromFile("program.txt"); // Error
//        pc.ReadProgramFromFile("program1.dat"); // Found
        pc.ReadProgramFromFile("test.dat"); // Found
//        pc.RunProgram();
    }
    catch (std::exception& e){
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
