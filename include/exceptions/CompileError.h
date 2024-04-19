//
// Created by Marci on 2024. 04. 19..
//

#ifndef NAGYHAZI_COMPILEERROR_H
#define NAGYHAZI_COMPILEERROR_H
#include "UniqueError.h"

class CompileError : public UniqueError {
public:
    explicit CompileError(const std::string& message, int lineNumber = -1) : UniqueError(message, lineNumber, "Compile error") {}
};

#endif //NAGYHAZI_COMPILEERROR_H
