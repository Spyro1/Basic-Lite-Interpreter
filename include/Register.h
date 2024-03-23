//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_REGISTER_H
#define NAGYHAZI_REGISTER_H

#include <string>
#include <vector>

#include "../memtrace.h"
using std::string;

class Register {
//    char* name;
    string name;
    float value = .0;

public:
    // -- Constructors --
    Register();
    explicit Register(string name, int defValue = 0);
    // -- Getters --
    const string& getName() const { return name; }
    float getValue() const { return value; }
    // -- Setters --
    void SetValue(float newValue) {value = newValue;}
    // -- Operators --
//    bool operator>(const Register& rhs) const { return value > rhs.getValue(); }
//    bool operator<(const Register& rhs) const { return value < rhs.getValue(); }
//    bool operator>=(const Register& rhs) const { return value >= rhs.getValue(); }
//    bool operator<=(const Register& rhs) const { return value <= rhs.getValue(); }
//    bool operator==(const Register& rhs) const { return name == rhs.getName(); }
//    bool operator!=(const Register& rhs) const { return name != rhs.getName(); }
    // -- Destructor --
    ~Register();
    // -- Static functions --
    static size_t FindRegisterIndex(const std::vector<Register> &registers, const string &name);
};


#endif //NAGYHAZI_REGISTER_H
