//
// Created by Marci on 2024. 04. 19..
//

#ifndef NAGYHAZI_UNIQUEERROR_H
#define NAGYHAZI_UNIQUEERROR_H

#include <exception>
#include <string>
using std::string;

/**
 * The UniqueError class is derived from the std::exception class and serves as a base class for defining
 * unique error types. It encapsulates an error message, an error type, and optionally, a line number.
 * This class allows for the creation of custom error types with specific error messages and types.
 */
class UniqueError : public std::exception {
protected:
    string errormessage; /// The error message describing the error condition.
    string errorType;    /// The type or category of the error.
public:
    /**
     * Constructs a UniqueError object with the given error message, optional line number, and error type.
     * @param message The error message describing the error condition.
     * @param lineNumber The line number in the source code where the error occurred. Default is -1.
     * @param type The type or category of the error. Default is "Error".
     */
    explicit UniqueError(const std::string& message, int lineNumber = -1, const std::string& type = "Error") : errorType(type) {
        errormessage = "[" + errorType + "]: " + message + (lineNumber > 0 ? string(" in line: ") + std::to_string(lineNumber) : "");
    }

    /**
     * This function overrides the std::exception::what() method to provide a C-style character string
     * describing the error condition.
     * @return A character string describing the error.
     */
    char const* what() const noexcept override { return errormessage.c_str(); }
};



#endif //NAGYHAZI_UNIQUEERROR_H
