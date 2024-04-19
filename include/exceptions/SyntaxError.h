//
// Created by Marci on 2024. 04. 19..
//

#ifndef NAGYHAZI_SYNTAXERROR_H
#define NAGYHAZI_SYNTAXERROR_H
#include "UniqueError.h"

class SyntaxError : public UniqueError {
public:
    explicit SyntaxError(const std::string& message, int lineNumber = -1) : UniqueError(message, lineNumber, "Syntax error") {}
};

#endif //NAGYHAZI_SYNTAXERROR_H
