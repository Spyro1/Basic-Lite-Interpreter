#include <iostream>
#include "Computer.h"

int main() {
    using namespace std;
    // Alapfeladat
    try {
        Computer pc;
//        pc.ReadProgramFromFile("program.txt"); // Error
        pc.ReadProgramFromFile("program1.txt"); // Found
    }
    catch (const char* e){
        cout << e << endl;
    }

    return 0;
}
