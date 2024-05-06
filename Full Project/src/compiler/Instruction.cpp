//
// Created by Szenes Márton on 2024. 03. 14..
//
#include <string>
#include <algorithm>
#include "../../include/compiler/Instruction.h"
#include "../../include/compiler/Expression.h"
#include "../../memtrace.h"

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

string Instruction::ProcessExpression(string &argument, vector<Register> &registers) {
    try{
        return Expression::Process(argument, registers);
    } catch (SyntaxError& se){
        throw SyntaxError(se.what(), lineNumber);
    } catch (CompileError& ce){
        throw CompileError(ce.what(), lineNumber);
    } catch (UniqueError& ue){
        throw UniqueError(ue.what(), lineNumber);
    } catch (std::exception& e){
        throw e.what();
    }
    // ÁTÍRVA EXPRESSION classba
}

//void Instruction::ReplaceCharacters(string& inputStr, const string& searched, const string& replace){
//    size_t pos = 0;
//    while ((pos = inputStr.find(searched, pos)) != nopos) {
//        inputStr.replace(pos, searched.length(), replace);
//        pos += replace.length();
//    }
//}
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





