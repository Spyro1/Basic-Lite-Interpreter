//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_REGISTER_H
#define NAGYHAZI_REGISTER_H


#include "../memtrace.h"

class Register {
    char* name;
    int value = -1;

public:
    // -- Constructors --
    Register();
    explicit Register(const char* name, int defValue = 0);
    // -- Getters --
    const char* getName() const;
    int getValue() const;
    // -- Destructor --
    ~Register();
};


#endif //NAGYHAZI_REGISTER_H
