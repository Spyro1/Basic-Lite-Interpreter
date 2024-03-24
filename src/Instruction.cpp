//
// Created by Szenes Márton on 2024. 03. 14..
//
#include <string>
#include <algorithm>
#include <stdexcept>
#include "../include/Instruction.h"

Instruction::Instruction() : lineNumber(0) { instrTy = InstructionType::NoType; }

Instruction::Instruction(int lineNumber_, const string &expression_) {
    this->expression = expression_;
    this->lineNumber = lineNumber_;
    instrTy = InstructionType::NoType;
}
int Instruction::getLineNumber() const {
    return lineNumber;
}
string Instruction::getType() const {
    switch (instrTy) {
        case Let: return "let";
        case Print: return "print";
        case Goto: return "goto";
        case If: return "if";
        case Read: return "read";
        default: return "unknown";
    }
}
string Instruction::getExpression() const {
    return expression;
}

std::ostream& operator<<(std::ostream &os, const Instruction& inst) {
//    os << std::to_string(inst.getLineNumber()) << std::string(" ") << inst.getType() << " " << inst.getExpression();
    return os;
}
Instruction::~Instruction() = default;

string Instruction::ProcessExpression(string &argument, vector<Register> &registers, ReturnType returnType) {
    using namespace std;
    // == Declare testing values ==
    string evaluated; // Result string
    size_t assignValueSignIndex = argument.find_first_of('='),
           equalsIndex = argument.find("=="),
           notEqualsIndex = argument.find("!="),
           plusIndex = argument.find_last_of('+'),
           minusIndex = argument.find_last_of('-'),
           multiplyIndex = argument.find_last_of('*'),
           divideIndex = argument.find_last_of('/'), // Index of +, -, *, / characters in argument
           firstOpeningBracket = argument.find_first_of('('), //FindIndexOf(argument, '(');
           firstClosingBracket = argument.find_first_of(')');//FindIndexOf(argument, ')');

    #pragma region == 0. level: Simplify +-
    ReplaceCharacters(argument, "--", "+");
    ReplaceCharacters(argument, "+-", "-");
    ReplaceCharacters(argument, "-+", "-");
    #pragma endregion

    #pragma region == 1. level: Assignment operator ==
    if (Exists(assignValueSignIndex) && assignValueSignIndex-1 != equalsIndex && assignValueSignIndex-1 != notEqualsIndex){
        string regName = argument.substr(0, assignValueSignIndex); // Get register name
        string valueToAssign = argument.substr(assignValueSignIndex + 1); // Separate after the equal sign

        size_t regIndex = Register::FindRegisterIndex(registers, regName);
        string evaluatedValueToAssign = ProcessExpression(valueToAssign, registers, Integer);
        auto newValue = std::stof(evaluatedValueToAssign);
        if (Exists(regIndex)) {
            // Assign value to existing register
            registers[regIndex].SetValue(newValue);
        } else {
            // Create new register and initialize it
            registers.emplace_back(regName, newValue);
        }
        return evaluatedValueToAssign;
    }

    #pragma endregion

    #pragma region == 2. level: Brackets ==

    if (firstOpeningBracket != firstClosingBracket) {
        size_t closeBracketPair = FindBracketPairIndex(argument, firstOpeningBracket);
        if (closeBracketPair == nopos) // Pair bracket not found
            throw std::logic_error(string("Syntax error: Missing brackets in line: ")+std::to_string(lineNumber));
        else {
            string betweenBrackets = argument.substr(firstOpeningBracket + 1,closeBracketPair-firstOpeningBracket - 1);
            string evaluatedBetweenBrackets = ProcessExpression(betweenBrackets, registers, returnType);
            ReplaceCharacters(argument, '(' + betweenBrackets + ')', evaluatedBetweenBrackets);
            // Call new evaluation
            evaluated = ProcessExpression(argument,registers,returnType);
            return evaluated; // Exit
        }
    }
    else if ((!Exists(firstOpeningBracket) && Exists(firstClosingBracket)) ||
              (Exists(firstOpeningBracket) && !Exists(firstClosingBracket))) {
        throw std::logic_error(string("Syntax error: Missing brackets in line: ")+std::to_string(lineNumber));
    }
    #pragma endregion


    #pragma region == 3/a. level: Boolean ==

        // == 2/1/1 : OR ==

        // == 2/1/2 : AND ==

        // == 2/1/3 : EQALS / NOT-EQUALS ==

        // == 2/1/4 : BIGGER / SMALLER / BIGGER-EQUALS / SMALLER-EQUALS ==

        // == 2/1/5 : NOT
    #pragma endregion


    #pragma region == 3/b. level: Integer ==

    // == 2/1/1 : PLUS / MINUS ==
    if (Exists(plusIndex) || Exists(minusIndex)) {
        int decider = 0; // 0: only one 1: PLUS, 2: MINUS
        if (Exists(plusIndex) && Exists(minusIndex)) { // Contains both
            decider = plusIndex > minusIndex ? 1 : 2;
        }
        if (Exists(plusIndex) && decider != 2) { // PLUS
            // Evaluate expression as adding
            string leftSide = argument.substr(0, plusIndex);
            string rightSide = argument.substr(plusIndex + 1, argument.length() - plusIndex - 1);
            string evaluatedLeftSide = ProcessExpression(leftSide, registers, returnType);
            string evaluatedRightSide = ProcessExpression(rightSide, registers, returnType);
            auto leftValue = stof(evaluatedLeftSide);
            auto rightValue = stof(evaluatedRightSide);
            evaluated = std::to_string(leftValue + rightValue);
            return evaluated;

        } else if (Exists(minusIndex) && decider != 1) { // MINUS
            // Evaluate expression as subtracting
            string leftSide = argument.substr(0, minusIndex);
            string rightSide = argument.substr(minusIndex + 1, argument.length() - minusIndex - 1);
            if (leftSide.empty()) leftSide = "0";
            if (rightSide.empty()) rightSide = "0";
            string evaluatedLeftSide = ProcessExpression(leftSide, registers, returnType);
            string evaluatedRightSide = ProcessExpression(rightSide, registers, returnType);
            auto leftValue = stof(evaluatedLeftSide);
            auto rightValue = stof(evaluatedRightSide);
            evaluated = std::to_string(leftValue - rightValue);
            return evaluated;
        }

    }
        // == 2/1/2 : MULTIPLY / DIVIDE
    else if (Exists(multiplyIndex = argument.find_last_of('*')) || Exists(divideIndex = argument.find_last_of('/'))) {
        int decider = 0; // 0: only one 1: MULTIPLY, 2: DIVIDE
        if (Exists(multiplyIndex) && Exists(divideIndex)) { // Contains both
            decider = plusIndex > divideIndex ? 1 : 2;
        }
        if (Exists(multiplyIndex) && decider != 2) { // MULTIPLY
            // Evaluate expression as multiplication
            string leftSide = argument.substr(0, multiplyIndex);
            string rightSide = argument.substr(multiplyIndex + 1, argument.length() - multiplyIndex - 1);
            string evaluatedLeftSide = ProcessExpression(leftSide, registers, returnType);
            string evaluatedRightSide = ProcessExpression(rightSide, registers, returnType);
            auto leftValue = stof(evaluatedLeftSide);
            auto rightValue = stof(evaluatedRightSide);
            evaluated = std::to_string(leftValue*rightValue);
            return evaluated;
        } else if (Exists(divideIndex) && decider != 1) { // DIVIDE
            // Evaluate expression as division
            string leftSide = argument.substr(0, divideIndex);
            string rightSide = argument.substr(divideIndex + 1, argument.length() - divideIndex - 1);
            string evaluatedLeftSide = ProcessExpression(leftSide, registers, returnType);
            string evaluatedRightSide = ProcessExpression(rightSide, registers, returnType);
            auto leftValue = stof(evaluatedLeftSide);
            auto rightValue = stof(evaluatedRightSide);
            evaluated = std::to_string((float)leftValue/(float)rightValue);
            return evaluated;
        }
    }
    #pragma endregion

    #pragma region == 4. level: Register Value ==
    // Test if register name exists. if not, then throw error
    size_t regIndex = Register::FindRegisterIndex(registers, argument);
//    if ( regIndex == -1 ) {
//        // Register name not found
//        throw std::runtime_error(string("Syntax error: Use of undeclared register in line: ") + std::to_string(lineNumber));
//    }
//    else {
    if (Exists(regIndex)) {
        // Return value from existing register
        evaluated = std::to_string(registers[regIndex].getValue());
        return evaluated;
    }
    #pragma endregion

    return argument;
}

void Instruction::ReplaceCharacters(string& inputStr, const string& searched, const string& replace){
    size_t pos = 0;
    while ((pos = inputStr.find(searched, pos)) != nopos) {
        inputStr.replace(pos, searched.length(), replace);
        pos += replace.length();
    }
}
int Instruction::CountCharacter(const string& str, char ch) {
    int count = 0;
    for (size_t i = 0; i < str.length(); i++)
        if (str[i] == ch)
            count++;
    return count;
}
string Instruction::RemoveWhiteSpace(const string& str){
    string shortened = str;
    //  Remove spaces using erase and remove_if
    shortened.erase(std::remove_if(shortened.begin(), shortened.end(), ::isspace), shortened.end());
    return shortened;
}
size_t Instruction::FindIndexOf(const string& str, char searched) {
    size_t found = str.find(searched);
    if (found > str.length()) {
        return nopos; // Return -1 if not found
    } else {
        return found; // Return index if found
    }
}
size_t Instruction::FindLastIndexOf(const string& str, char searched) {
    size_t found = str.find_last_of(searched);
    if (found > str.length()) {
        return nopos; // Return -1 if not found
    } else {
        return found; // Return index if found
    }
}
size_t Instruction::FindBracketPairIndex(string str, size_t openPos, char OpenPair, char ClosePair)
{
    size_t closePos = openPos;
    int matching = 1;
    while (matching > 0 && closePos < str.length())
    {
        char c = str[++closePos];
        if (c == OpenPair)
            matching++;
        else if (c == ClosePair)
            matching--;
    }
    if (closePos >= str.length())
        return -1; // Couldn't find pair
    else
        return closePos; // Pair found
}







