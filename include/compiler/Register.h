//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_REGISTER_H
#define NAGYHAZI_REGISTER_H

#include <string>
#include <vector>

using std::string;

class Register {
    string name; // Register name
    float value = 0; // Register value
public:
    // -- Constructors --
    Register();
    explicit Register(const string& name, float defValue = 0);
    // -- Getters --
    const string& getName() const { return name; }
    float getValue() const { return value; }
    // -- Setters --
    void SetValue(float newValue) { value = newValue; }
    // -- Destructor --
    ~Register();
    // -- Static functions --

};


#endif //NAGYHAZI_REGISTER_H
