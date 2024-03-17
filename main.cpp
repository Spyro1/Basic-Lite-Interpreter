#include <iostream>
#include "include/Computer.h"

int main() {
    using namespace std;
    // Alapfeladat
    try {
        Computer pc;
//        pc.ReadProgramFromFile("program.txt"); // Error
        pc.ReadProgramFromFile("program1.txt"); // Found
    }
    catch (std::exception& e){
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
