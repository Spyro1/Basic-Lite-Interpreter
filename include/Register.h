//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_REGISTER_H
#define NAGYHAZI_REGISTER_H

#include <string>

#include "../memtrace.h"
using std::string;

class Register {
//    char* name;
    string name;
    int value = 0;

public:
    // -- Constructors --
    Register();
    explicit Register(string name, int defValue = 0);
    // -- Getters --
    const string& getName() const { return name; };
    const int getValue() const {return value; };
    // -- Operators --
    bool operator>(const Register& rhs) const { return value > rhs.getValue(); }
    bool operator<(const Register& rhs) const { return value < rhs.getValue(); }
    bool operator>=(const Register& rhs) const { return value >= rhs.getValue(); }
    bool operator<=(const Register& rhs) const { return value <= rhs.getValue(); }
    bool operator==(const Register& rhs) const { return name == rhs.getName(); }
    bool operator!=(const Register& rhs) const { return name != rhs.getName(); }
    // -- Destructor --
    ~Register();
};


#endif //NAGYHAZI_REGISTER_H
