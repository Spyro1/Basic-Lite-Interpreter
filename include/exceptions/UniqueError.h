//
// Created by Marci on 2024. 04. 19..
//

#ifndef NAGYHAZI_UNIQUEERROR_H
#define NAGYHAZI_UNIQUEERROR_H
#include <exception>
#include <string>
using std::string;

class UniqueError : public std::exception {
protected:
    string errormessage;
    string errorType;
public:
    explicit UniqueError(const std::string& message, int lineNumber = -1, const std::string& type = "Error") : errorType(type) {
        errormessage = "[" + errorType + "]: " + message + (lineNumber > 0 ? string(" in line: ") + std::to_string(lineNumber) : "");
    }
    char const* what() const throw() override { return errormessage.c_str(); }
};


#endif //NAGYHAZI_UNIQUEERROR_H
