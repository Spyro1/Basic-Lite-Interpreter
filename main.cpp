#include <iostream>
#include "Computer.h"

int main() {
    using namespace std;
    // Alapfeladat
    try {
        Computer pc;
//        pc.ReadProgramFromFile("program.txt");
    }
    catch (const char* e){
        cout << e << endl;
    }

    return 0;
}
