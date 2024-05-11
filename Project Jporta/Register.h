//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_REGISTER_H
#define NAGYHAZI_REGISTER_H

#include <string>
#include <vector>

using std::string;

/**
 * Represents a register with a name and a value.
 */
class Register {
    string name;     // Register name
    float value = 0; // Register value
public:

    // == Constructors ==
    /**
     * Creates a Register object that stores a register's name and float value
     * @param name Name of the register
     * @param defValue Value of the register
     */
    explicit Register(const string& name = "", float defValue = 0) : name(name), value(defValue) { }

    // == Getters ==
    /**
     * Get the name of the register
     * @return Name of the register
     */
    const string& getName() const { return name; }
    /**
     * Get the value of the register
     * @return Value of the register
     */
    float getValue() const { return value; }

    // == Setters ==
    /**
     * Set the value of the register
     * @param newValue New value of the register
     */
    void SetValue(float newValue) { value = newValue; }
};


#endif //NAGYHAZI_REGISTER_H
