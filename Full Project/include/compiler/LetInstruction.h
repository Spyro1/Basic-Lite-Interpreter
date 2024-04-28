//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_LETINSTRUCTION_H
#define NAGYHAZI_LETINSTRUCTION_H

#include "Instruction.h"

class LetInstruction : public Instruction{
public:

    // == Constructors ==
    /**
     * This constructor initializes a new instance of the LetInstruction class, which represents an instruction
     * for assigning a value to a variable. It inherits from the Instruction class.
     * @param lineNumber An integer representing the line number in the code where this instruction occurs.
     * It helps with debugging and tracing execution flow.
     * @param expression A constant reference to a string representing any expression associated with the assignment
     * operation. This could be the variable name and the value to assign, or more complex expressions involving
     * variables and constants.
     */
    LetInstruction(int lineNumber, const string& expression);

    // == Virtual function ==
    /**
     * This function is a virtual method intended to execute a specific instruction within a sequence of instructions.
     * It operates on a set of registers and a list of instruction objects, moving through the instructions based on
     * the provided instruction index.
     * @param registers A reference to a vector of Register objects representing the computer's registers.
     * These registers hold data that the instructions may operate on or modify.
     * @param instructions A reference to a vector of pointers to Instruction objects.
     * These represent the sequence of instructions to be executed.
     * @param instructionIndex A reference to an integer representing the current index of the instruction to be
     * executed within the instructions vector. This index will be updated to point to the next instruction to
     * execute after this function call.
     */
    void Execute(vector<Register>& registers, vector<Instruction*>& instructions, int& instructionIndex) override;
};


#endif //NAGYHAZI_LETINSTRUCTION_H
