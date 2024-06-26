//
// Created by Szenes Márton on 2024. 03. 14..
//
#include <string>
#include <algorithm>
#include "Instruction.h"
#include "memtrace.h"

Instruction::Instruction(int lineNumber_, const string &expression_, InstructionType instructionType) : lineNumber(lineNumber_), expression(expression_), instrTy(instructionType) {}

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
    return os << std::to_string(inst.getLineNumber()) << std::string(" ") << inst.getInstructionTypeStr() << string(" ") << inst.getExpression();
}

string Instruction::ProcessExpression(string &argument, std::map<string, float>& registers) {
    using namespace std;
    // = Declare testing values =
    string evaluated; // Result string
    float leftValue, rightValue; // Evaluated left or right side of operation
    // region == 0. level: Simplify +- ==
    ReplaceCharacters(argument, "--", "+");
    ReplaceCharacters(argument, "+-", "-");
    ReplaceCharacters(argument, "-+", "-");
    // endregion

    // = Find operator indexes =
    size_t assignValueSignIndex = argument.find('='),
           orIndex = argument.rfind("||"),
           andIndex = argument.rfind("&&"),
           biggerIndex = argument.rfind('>'),
           smallerIndex = argument.rfind('<'),
           equalsIndex = argument.rfind("=="),
           notEqualsIndex = argument.rfind("!="),
           notIndex = argument.rfind('!'),
           plusIndex = argument.rfind('+'),
           minusIndex = argument.rfind('-'),
           multiplyIndex = argument.rfind('*'),
           divideIndex = argument.rfind('/'),
           modIndex = argument.rfind('%'),
           firstOpeningBracket = argument.find('('),
           firstClosingBracket = argument.rfind(')');


    // region == 1. level: Assignment operator ==
    if (Exists(assignValueSignIndex) && assignValueSignIndex != equalsIndex && assignValueSignIndex-1 != notEqualsIndex && assignValueSignIndex-1 != biggerIndex && assignValueSignIndex-1 != smallerIndex){
        string regName = argument.substr(0, assignValueSignIndex); // Get register name
        string valueToAssign = argument.substr(assignValueSignIndex + 1); // Separate after the equal sign
        string evaluatedValueToAssign = ProcessExpression(valueToAssign, registers); // Process right value
        auto newValue = std::stof(evaluatedValueToAssign); // Convert to float
        registers[regName] = newValue; // Assign value to register
        return evaluatedValueToAssign;
    }
    // endregion

    // region == 2. level: Brackets ==

    if (Exists(firstOpeningBracket) && Exists(firstClosingBracket)) {
        size_t closeBracketPair = FindBracketPairIndex(argument, firstOpeningBracket);
        if (closeBracketPair == nopos) // Pair bracket not found
            throw SyntaxError("Missing brackets", lineNumber);
        else {
            string betweenBrackets = argument.substr(firstOpeningBracket + 1,closeBracketPair-firstOpeningBracket - 1);
            string evaluatedBetweenBrackets = ProcessExpression(betweenBrackets, registers);
            ReplaceCharacters(argument, '(' + betweenBrackets + ')', evaluatedBetweenBrackets);
            // Call new evaluation
            evaluated = ProcessExpression(argument,registers);
            return evaluated; // Exit
        }
    }
    else if ((!Exists(firstOpeningBracket) && Exists(firstClosingBracket)) || (Exists(firstOpeningBracket) && !Exists(firstClosingBracket))) {
        throw SyntaxError("Missing brackets", lineNumber);
    }
    else if (Exists(firstOpeningBracket) || Exists(firstClosingBracket)){
        throw SyntaxError("Missing brackets", lineNumber);
    }
    // endregion

    // region == 3/a. level: Boolean ==

    // == 2/1/1 : OR ==
    if (Exists(orIndex)){
        // Evaluate expression as OR logic
        SplitAndProcessArguments(argument, registers, orIndex, leftValue, rightValue, 2);
        evaluated = (leftValue != 0) || (rightValue != 0) ? '1' : '0';
        return evaluated;
    }
    // == 2/1/2 : AND ==
    else if (Exists(andIndex)){
        // Evaluate expression as AND logic
        SplitAndProcessArguments(argument, registers, andIndex, leftValue, rightValue, 2);
        evaluated = (leftValue != 0) && (rightValue != 0) ? '1' : '0';
        return evaluated;
    }
    // == 2/1/3 : EQALS / NOT-EQUALS ==
    else if (Exists(equalsIndex) || Exists(notEqualsIndex)){
        int decider = 0; // 0: only one 1: EQ, 2: NOTEQ
        if (Exists(equalsIndex) && Exists(notEqualsIndex)) { // Contains both
            decider = equalsIndex > notEqualsIndex ? 1 : 2;
        }
        if (Exists(equalsIndex) && decider != 2) { // EQ
            // Evaluate expression as EQ logic
            SplitAndProcessArguments(argument, registers, equalsIndex, leftValue, rightValue, 2);
            evaluated = leftValue == rightValue ? '1' : '0';
        }
        else if (Exists(notEqualsIndex) && decider != 1) { // NOTEQ
            // Evaluate expression as NOTEQ logic
            SplitAndProcessArguments(argument, registers, notEqualsIndex, leftValue, rightValue, 2);
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
        if (Exists(biggerIndex) && decider != 2) { // BIGGER
            // Evaluate expression as BIGGER
            if (biggerIndex + 1 == assignValueSignIndex){
                SplitAndProcessArguments(argument, registers, biggerIndex, leftValue, rightValue, 2);
                evaluated = leftValue >= rightValue ? '1' : '0';
            }
            else {
                SplitAndProcessArguments(argument, registers, biggerIndex, leftValue, rightValue);
                evaluated = leftValue > rightValue ? '1' : '0';
            }
        }
        else if (Exists(smallerIndex) && decider != 1) { // SMALLER
            // Evaluate expression as SMALLER
            if (smallerIndex + 1 == assignValueSignIndex){
                SplitAndProcessArguments(argument, registers, smallerIndex, leftValue, rightValue, 2);
                evaluated = leftValue <= rightValue ? '1' : '0';
            }
            else {
                SplitAndProcessArguments(argument, registers, smallerIndex, leftValue, rightValue);
                evaluated = leftValue < rightValue ? '1' : '0';
            }
        }
        return evaluated;
    }
    // == 2/1/5 : NOT
    else if (Exists(notIndex)){
        // Evaluate expression as EQ logic
        SplitAndProcessArguments(argument, registers, notIndex, leftValue, rightValue);
        evaluated = rightValue == 0 ? '1' : '0';
        return evaluated;
    }
    // endregion

    // region == 3/b. level: Integer ==

    // == 2/1/1 : PLUS / MINUS ==
    if (Exists(plusIndex) || Exists(minusIndex)) {
        int decider = 0; // 0: only one 1: PLUS, 2: MINUS
        if (Exists(plusIndex) && Exists(minusIndex)) { // Contains both
            decider = plusIndex > minusIndex ? 1 : 2;
        }
        if (Exists(plusIndex) && decider != 2) { // PLUS
            // Evaluate expression as adding
            SplitAndProcessArguments(argument, registers, plusIndex, leftValue, rightValue);
            evaluated = std::to_string(leftValue + rightValue);
        }
        else if (Exists(minusIndex) && decider != 1) { // MINUS
            // Evaluate expression as subtracting
            SplitAndProcessArguments(argument, registers, minusIndex, leftValue, rightValue);
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
            SplitAndProcessArguments(argument, registers, multiplyIndex, leftValue, rightValue);
            evaluated = std::to_string(leftValue * rightValue);
        }
        else if (Exists(divideIndex) && (decider == 2 || decider == 0)) { // DIVIDE
            // Evaluate expression as division
            SplitAndProcessArguments(argument, registers, divideIndex, leftValue, rightValue);
            evaluated = std::to_string(leftValue / rightValue);
        }
        else if (Exists(modIndex) && (decider == 3 || decider == 0)) { // DIVIDE
            // Evaluate expression as division
            SplitAndProcessArguments(argument, registers, modIndex, leftValue, rightValue);
            evaluated = std::to_string((int)leftValue % (int)rightValue);
        }
        return evaluated;
    }
    // endregion

    // region == 4. level: Register Value ==
    // Test if register name exists. if yes, then return value
    if (registers.find(argument) != registers.end()) {
        return std::to_string(registers[argument]);
    }
    // endregion

    // Test if argument is still a register name that is not defined, throw error
    if (!isNumber(argument)){
        throw SyntaxError(string("Unrecognized register name \"" + argument + '\"'), lineNumber);
    }

    // Return evaluated number value
    return argument;
}

void Instruction::ReplaceCharacters(string& inputStr, const string& searched, const string& replace){
    size_t pos = 0;
    while ((pos = inputStr.find(searched, pos)) != nopos) {
        inputStr.replace(pos, searched.length(), replace);
        pos += replace.length();
    }
}

string Instruction::RemoveWhiteSpace(const string& str){
    string shortened = str;
    //  Remove spaces using erase and remove_if
    shortened.erase(std::remove_if(shortened.begin(), shortened.end(), ::isspace), shortened.end());
    return shortened;
}
size_t Instruction::FindBracketPairIndex(string str, size_t openPos, char OpenPair, char ClosePair) {
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
        return nopos; // Couldn't find pair
    else
        return closePos; // Pair found
}

void Instruction::SplitAndProcessArguments(const string &inputArg, std::map<string, float>& registers, size_t operatorIndex, float &evaluatedArg1, float &evaluatedArg2, size_t operatorChars) {
    string leftSide = inputArg.substr(0, operatorIndex);
    string rightSide = inputArg.substr(operatorIndex + operatorChars, inputArg.length() - operatorIndex);
    if (leftSide.empty()) leftSide = "0";
    if (rightSide.empty()) rightSide = "0";
    string evaluatedLeftSide = ProcessExpression(leftSide, registers);
    string evaluatedRightSide = ProcessExpression(rightSide, registers);
    evaluatedArg1 = stof(evaluatedLeftSide);
    evaluatedArg2 = stof(evaluatedRightSide);
}

bool Instruction::isNumber(const std::string& str) {
    size_t i = 0;
    bool hasDigits = false;
    // Check for optional presign
    if (i < str.length() && (str[i] == '+' || str[i] == '-')) { i++; }
    // Check for digits
    while (i < str.length() && (std::isdigit(str[i]) || str[i] == '.' || str[i] == ',')) {
        hasDigits = true;
        i++;
    }
    return i == str.length() && hasDigits;
}