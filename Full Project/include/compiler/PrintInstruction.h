//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_PRINTINSTRUCTION_H
#define NAGYHAZI_PRINTINSTRUCTION_H

#include "Instruction.h"

/**
 * The PrintInstruction class represents an instruction to print value to the output. It inherits from the Instruction class.
 */
class PrintInstruction : public Instruction {
public:

    // == Constructors ==
    /**
     * This constructor initializes a new instance of the PrintInstruction class, which represents an instruction
     * for printing output to the console. It inherits from the Instruction class.
     * @param lineNumber An integer representing the line number in the code where this instruction occurs.
     * It helps with debugging and tracing execution flow.
     * @param expression A constant reference to a string representing the content or message to be printed.
     * This could include variables, literals, or expressions that need to be evaluated and printed.
     */
    PrintInstruction(int lineNumber, const string& expression);

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


#endif //NAGYHAZI_PRINTINSTRUCTION_H
