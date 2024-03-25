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
string Instruction::getInstructionTypeStr() const {
    switch (instrTy) {
        case Let: return LET;
        case Print: return PRINT;
        case Goto: return GOTO;
        case If: return IF;
        case Read: return READ;
        default: return "unknown";
    }
}
InstructionType Instruction::getInstructionType() const{
    return instrTy;
}
string Instruction::getExpression() const {
    return expression;
}

std::ostream& operator<<(std::ostream &os, const Instruction& inst) {
//    os << std::to_string(inst.getLineNumber()) << std::string(" ") << inst.getInstructionTypeStr() << " " << inst.getExpression();
    return os;
}
Instruction::~Instruction() = default;

string Instruction::ProcessExpression(string &argument, vector<Register> &registers) {
    using namespace std;
    // == Declare testing values ==
    string evaluated; // Result string
    float leftValue, rightValue;
    size_t assignValueSignIndex = argument.find_first_of('='),
           orIndex = argument.find_last_of("||"),
           andIndex = argument.find_last_of("&&"),
           biggerIndex = argument.find_last_of('>' ),
           smallerIndex = argument.find_last_of('<'),
           equalsIndex = argument.find("=="),
           notEqualsIndex = argument.find("!="),
           plusIndex = argument.find_last_of('+'),
           minusIndex = argument.find_last_of('-'),
           multiplyIndex = argument.find_last_of('*'),
           divideIndex = argument.find_last_of('/'),
           modIndex = argument.find_last_of('%'), // Index of +, -, *, /, % characters in argument
           firstOpeningBracket = argument.find_first_of('('), //FindIndexOf(argument, '(');
           firstClosingBracket = argument.find_first_of(')');//FindIndexOf(argument, ')');

    #pragma region == 0. level: Simplify +-
    ReplaceCharacters(argument, "--", "+");
    ReplaceCharacters(argument, "+-", "-");
    ReplaceCharacters(argument, "-+", "-");
    #pragma endregion

    #pragma region == 1. level: Assignment operator ==
    if (Exists(assignValueSignIndex) && assignValueSignIndex != equalsIndex && assignValueSignIndex != notEqualsIndex){
        string regName = argument.substr(0, assignValueSignIndex); // Get register name
        string valueToAssign = argument.substr(assignValueSignIndex + 1); // Separate after the equal sign

        size_t regIndex = Register::FindRegisterIndex(registers, regName);
        string evaluatedValueToAssign = ProcessExpression(valueToAssign, registers);
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

    if (Exists(firstOpeningBracket) && Exists(firstClosingBracket)) {
        size_t closeBracketPair = FindBracketPairIndex(argument, firstOpeningBracket);
        if (closeBracketPair == nopos) // Pair bracket not found
            throw std::logic_error(string("Syntax error: Missing brackets in line: ")+std::to_string(lineNumber));
        else {
            string betweenBrackets = argument.substr(firstOpeningBracket + 1,closeBracketPair-firstOpeningBracket - 1);
            string evaluatedBetweenBrackets = ProcessExpression(betweenBrackets, registers);
            ReplaceCharacters(argument, '(' + betweenBrackets + ')', evaluatedBetweenBrackets);
            // Call new evaluation
            evaluated = ProcessExpression(argument,registers);
            return evaluated; // Exit
        }
    }
    else if ((!Exists(firstOpeningBracket) && Exists(firstClosingBracket)) ||
              (Exists(firstOpeningBracket) && !Exists(firstClosingBracket))) {
        throw std::logic_error(string("Syntax error: Missing brackets in line: ")+std::to_string(lineNumber));
    }
    else if (Exists(firstOpeningBracket) || Exists(firstClosingBracket)){
        throw std::logic_error(string("Syntax error: Missing brackets in line: ")+std::to_string(lineNumber));
    }
    #pragma endregion


    #pragma region == 3/a. level: Boolean ==

    // == 2/1/1 : OR ==
    if (Exists(orIndex)){
        // Evaluate expression as OR logic
        SplitAndProcessArguemnts(argument,registers, orIndex,leftValue, rightValue);
        evaluated = (leftValue != 0) || (rightValue != 0) ? '1' : '0';
        return evaluated;
    }
    // == 2/1/2 : AND ==
    else if (Exists(andIndex)){
        // Evaluate expression as AND logic
        SplitAndProcessArguemnts(argument,registers, andIndex,leftValue, rightValue);
        evaluated = (leftValue != 0) && (rightValue != 0) ? '1' : '0';
        return evaluated;
    }
    // == 2/1/3 : EQALS / NOT-EQUALS ==
    else if (Exists(equalsIndex) || Exists(notEqualsIndex)){
        int decider = 0; // 0: only one 1: EQ, 2: NOTEQ
        if (Exists(equalsIndex) && Exists(notEqualsIndex)) { // Contains both
            decider = equalsIndex > notEqualsIndex ? 1 : 2;
        }
        if (Exists(equalsIndex) && decider != 2) { // PLUS
            // Evaluate expression as adding
            SplitAndProcessArguemnts(argument,registers, equalsIndex,leftValue, rightValue);
            evaluated = leftValue == rightValue ? '1' : '0';
        }
        else if (Exists(notEqualsIndex) && decider != 1) { // MINUS
            // Evaluate expression as subtracting
            SplitAndProcessArguemnts(argument,registers, notEqualsIndex,leftValue, rightValue);
            evaluated = leftValue != rightValue ? '1' : '0';
        }
        return evaluated;
    }
    // == 2/1/4 : BIGGER / SMALLER / BIGGER-EQUALS / SMALLER-EQUALS ==
    else if (Exists(biggerIndex) || Exists(smallerIndex)){
        int decider = 0; // 0: only one 1: BIGGER, 2: SMALLER
        if (Exists(biggerIndex) && Exists(smallerIndex)) { // Contains both
            decider = biggerIndex > smallerIndex ? 1 : 2;
        }
        if (Exists(biggerIndex) && decider != 2) { // PLUS
            // Evaluate expression as adding
            SplitAndProcessArguemnts(argument,registers, plusIndex,leftValue, rightValue);
            if (biggerIndex + 1 == assignValueSignIndex) evaluated = leftValue >= rightValue ? '1' : '0';
            else evaluated = leftValue > rightValue ? '1' : '0';
        }
        else if (Exists(smallerIndex) && decider != 1) { // MINUS
            // Evaluate expression as subtracting
            SplitAndProcessArguemnts(argument,registers, minusIndex,leftValue, rightValue);
            if (smallerIndex + 1 == assignValueSignIndex) evaluated = leftValue <= rightValue ? '1' : '0';
            else evaluated = leftValue < rightValue ? '1' : '0';
        }
        return evaluated;
    }

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
            SplitAndProcessArguemnts(argument,registers, plusIndex,leftValue, rightValue);
            evaluated = std::to_string(leftValue + rightValue);
        }
        else if (Exists(minusIndex) && decider != 1) { // MINUS
            // Evaluate expression as subtracting
            SplitAndProcessArguemnts(argument,registers, minusIndex,leftValue, rightValue);
            evaluated = std::to_string(leftValue - rightValue);
        }
        return evaluated;
    }
        // == 2/1/2 : MULTIPLY / DIVIDE
    else if (Exists(multiplyIndex) || Exists(divideIndex) || Exists(modIndex)) {
        int decider = 0; // 0: only one 1: MULTIPLY, 2: DIVIDE, 3: MOD
        if (Exists(multiplyIndex) && Exists(divideIndex) && Exists(modIndex)) { // Contains both
            size_t indexes[] = {multiplyIndex, divideIndex, modIndex};
            decider = (int)std::distance(indexes, std::max_element(indexes, indexes + 3)) + 1;
        }
        else if (Exists(multiplyIndex) && Exists(divideIndex)) decider = multiplyIndex > divideIndex ? 1 : 2;
        else if (Exists(modIndex) && Exists(divideIndex)) decider = modIndex > divideIndex ? 3 : 2;
        else if (Exists(multiplyIndex) && Exists(modIndex)) decider = multiplyIndex > modIndex ? 1 : 3;

        if (Exists(multiplyIndex) && (decider == 1 || decider == 0)) { // MULTIPLY
            // Evaluate expression as multiplication
            SplitAndProcessArguemnts(argument,registers, multiplyIndex,leftValue, rightValue);
            evaluated = std::to_string(leftValue * rightValue);
        }
        else if (Exists(divideIndex) && (decider == 2 || decider == 0)) { // DIVIDE
            // Evaluate expression as division
            SplitAndProcessArguemnts(argument,registers, divideIndex,leftValue, rightValue);
            evaluated = std::to_string(leftValue / rightValue);
        }
        else if (Exists(modIndex) && (decider == 3 || decider == 0)) { // DIVIDE
            // Evaluate expression as division
            SplitAndProcessArguemnts(argument,registers, modIndex,leftValue, rightValue);
            evaluated = std::to_string((int)leftValue % (int)rightValue);
        }
        return evaluated;
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

void Instruction::SplitAndProcessArguemnts(const string &inputArg, vector<Register>& registers, size_t operatorIndex, float &evaluatedArg1, float &evaluatedArg2) {
    string leftSide = inputArg.substr(0, operatorIndex);
    string rightSide = inputArg.substr(operatorIndex + 1, inputArg.length() - operatorIndex - 1);
    if (leftSide.empty()) leftSide = "0";
    if (rightSide.empty()) rightSide = "0";
    string evaluatedLeftSide = ProcessExpression(leftSide, registers);
    string evaluatedRightSide = ProcessExpression(rightSide, registers);
    evaluatedArg1 = stof(evaluatedLeftSide);
    evaluatedArg2 = stof(evaluatedRightSide);
}







