//
// Created by Marci on 2024. 04. 19..
//

#ifndef NAGYHAZI_COMPILEERROR_H
#define NAGYHAZI_COMPILEERROR_H
#include "UniqueError.h"

/**
 * The CompileError class is derived from the UniqueError class and is used to represent errors
 * encountered during the compilation process.
 *
 * This class inherits the message and line number information from its base class UniqueError,
 * and adds the specific error type "Compile error".
 */
class CompileError : public UniqueError {
public:
    /**
     * Constructs a CompileError object with the given error message and optional line number.
     * @param message The error message describing the issue encountered during compilation.
     * @param lineNumber The line number in the source code where the error occurred. Default is -1.
     */
    explicit CompileError(const std::string& message, int lineNumber = -1)
            : UniqueError(message, lineNumber, "Compile error") {}
};

#endif //NAGYHAZI_COMPILEERROR_H
