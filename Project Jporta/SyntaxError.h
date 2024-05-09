//
// Created by Marci on 2024. 04. 19..
//

#ifndef NAGYHAZI_SYNTAXERROR_H
#define NAGYHAZI_SYNTAXERROR_H

#include "UniqueError.h"

/**
 * The SyntaxError class is derived from the UniqueError class and is used to represent errors
 * caused by syntax issues in code.
 * This class inherits the message and line number information from its base class UniqueError,
 * and adds the specific error type "Syntax error".
 */
class SyntaxError : public UniqueError {
public:
    /**
     * Constructs a SyntaxError object with the given error message and optional line number.
     * @param message The error message describing the syntax issue encountered.
     * @param lineNumber The line number in the source code where the syntax error occurred. Default is -1.
     */
    explicit SyntaxError(const std::string& message, int lineNumber = -1)
            : UniqueError(message, lineNumber, "Syntax error") {}
};


#endif //NAGYHAZI_SYNTAXERROR_H
