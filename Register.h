//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_REGISTER_H
#define NAGYHAZI_REGISTER_H

//#include <locale>

class Register {
    char* name;
    int value = -1;

public:
    // -- Constructors --
    Register();
    explicit Register(const char* name, int defValue = 0);

    const char* getName() const;
    int getValue() const;

    ~Register();
};


#endif //NAGYHAZI_REGISTER_H
