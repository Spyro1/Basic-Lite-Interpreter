//
// Created by Marci on 2024. 05. 06..
//

#ifndef NAGYHAZI_EXPRESSION_H
#define NAGYHAZI_EXPRESSION_H

#include <string>
#include "Register.h"

using std::string;
using std::vector;

#define nopos string::npos

class Expression {
public:
    // == Static functions ==
    static string Process(string& expression, std::vector<Register>& registers);
    /**
     * Check if a string represents a valid number.
     * @param str The string to be checked.
     * @return True if the string represents a number, false otherwise.
     */
    static bool isNumber(const string &str);
    static void SplitAndProcessArguments(const string& inputArg, vector<Register>& registers, size_t operatorIndex, float& evaluatedArg1, float& evaluatedArg2, size_t operatorChars = 1) ;
    static inline bool Exists(size_t value) { return value != string::npos; }
    static size_t FindBracketPairIndex(string str, size_t openPos, char OpenPair = '(', char ClosePair = ')');
    static size_t FindRegisterIndex(const std::vector<Register> &registers, const string &name);
};


#endif //NAGYHAZI_EXPRESSION_H
