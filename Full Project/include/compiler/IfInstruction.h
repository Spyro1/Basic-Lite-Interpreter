//
// Created by marci on 2024. 03. 16..
//

#ifndef NAGYHAZI_IFINSTRUCTION_H
#define NAGYHAZI_IFINSTRUCTION_H

#include "Instruction.h"

/**
 * The IfInstruction class represents an instruction for conditional branching based on a specified expression. It inherits from the Instruction class.
 */
class IfInstruction : public Instruction{
public:

    // == Constructors ==
    /**
     * This constructor initializes a new instance of the IfInstruction class, which represents an instruction
     * for conditional branching based on a specified expression. It inherits from the Instruction class.
     * @param lineNumber An integer representing the line number in the code where this instruction occurs.
     * It helps with debugging and tracing execution flow.
     * @param expression A constant reference to a string representing the conditional expression associated with the
     * if statement. This expression determines whether the code after this should be executed or the second code after
     * this based on its evaluation.
     */
    IfInstruction(int lineNumber, const string& expression);

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


#endif //NAGYHAZI_IFINSTRUCTION_H
