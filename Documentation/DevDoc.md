## explicit Command(Computer& pc, const char* cmdStr = "")
****

Creates a command that the user can use from the IDE
@param pc Reference to the computer compiling the code
@param cmdStr String literal fo the command


## virtual void operator()(const string& filename, bool& active) = 0
****

Calls the Function dedicated to this command


## bool operator==(const string& commandStr)
****

Checks if the given string is equal to the command
@param str command tester string
@return equality of the string to the command


## virtual ~Command() = default
****

Destroys the command object.


## class CompileError : public UniqueError {
public:
    /**
     * Constructs a CompileError object with the given error message and optional line number.
     * @param message The error message describing the issue encountered during compilation.
     * @param lineNumber The line number in the source code where the error occurred. Default is -1.
     */
    explicit CompileError(const std::string& message, int lineNumber = -1)
****

@brief Represents an error that occurs during compilation.

The CompileError class is derived from the UniqueError class and is used to represent errors
encountered during the compilation process.

This class inherits the message and line number information from its base class UniqueError,
and adds the specific error type "Compile error".


## explicit Computer()
****

Creates a computer object that can run a BASIC-lite program.


## size_t getInstructionCount() const
****

Gives the number of instructions in the program
@return Number of instructions


## void ReadProgramFromFile(const string& filename)
****

Reads the program from the given file into the 'instructions' list.
@param filename The name of the file that contains the program.


## void NewInstruction(const string& programLine)
****

Evaluates the read string line.
If the line number is positive, then the computer adds it to the instruction list,
if the number is negative, then the computer removes the corresponding instrcution
with the absolute value of the given line number.
@param programLine Inputted line containing the instruction: <lineNumber> <command> <argument>


## void RunProgram()
****

Runs the program: Executes the instructions based on the instructionIndex value
which is modified according to the previous instruction.


## void ClearProgram()
****

Clears the list of instructions from the program memory and resets the instruction count to 0.


## friend std::ostream& operator<<(std::ostream& os, const Computer& pc)
****

Lists the instructions stored in the memory of the computer.
@return Returns a string containing all the instructions displayed line by line.


## ~Computer()
****

Destroys the Computer object, cleans up resources allocated by the Computer.


## void ExecuteNextInstruction()
****

Executes the next instruction in the line based on the instrcutionIndex's value


## class EndCommand : public Command{
public:
    // == Constructor ==
    /**
     * Constructs a EndCommand object.
     * @param pc A reference to the Computer object.
     */
    explicit EndCommand(Computer& pc)
****

The EndCommand class represents a command that closes the interface upon executed.
Inherits from the Command class.


## void operator()(const string& filename, bool& active) override
****

Executes the End command.
@param filename The name of the file. (Unused)
@param active A boolean reference indicating whether the interface is active.


## GotoInstruction(int lineNumber, const string& expression)
****

This constructor initializes a new instance of the GotoInstruction class, which represents an instruction
to unconditionally jump to a specified line number in the code. It inherits from the Instruction class.
@param lineNumber An integer representing the line number in the code where this instruction occurs.
It helps with debugging and tracing execution flow.
@param expression A constant reference to a string representing the expression containing the line number
to which the program will jump to.


## void Execute(vector<Register>& registers, vector<Instruction*>& instructions, int& instructionIndex) override
****

This function is a virtual method intended to execute a specific instruction within a sequence of instructions.
It operates on a set of registers and a list of instruction objects, moving through the instructions based on
the provided instruction index.
@param registers A reference to a vector of Register objects representing the computer's registers.
These registers hold data that the instructions may operate on or modify.
@param instructions A reference to a vector of pointers to Instruction objects.
These represent the sequence of instructions to be executed.
@param instructionIndex A reference to an integer representing the current index of the instruction to be
executed within the instructions vector. This index will be updated to point to the next instruction to
execute after this function call.


## class HelpCommand : public Command{
public:
    // == Constructor ==
    /**
     * Constructs a HelpCommand object.
     * @param pc A reference to the Computer object.
     */
    explicit HelpCommand(Computer& pc)
****

The HelpCommand class represents a command that prints the possible commands to the standard output.
Inherits from the Command class.


## void operator()(const string& filename, bool& active) override
****

Executes the Help command.
@param filename The name of the file. (Unused)
@param active A boolean reference indicating whether the interface is active.


## explicit IDE()
****

Constructs an IDE object, initializes the IDE with default commands.


## void Run()
****

This function runs the IDE on the terminal, allowing users to interact with it.


## ~IDE()
****

Destroys the IDE object, cleans up resources allocated by the IDE.


## IfInstruction(int lineNumber, const string& expression)
****

This constructor initializes a new instance of the IfInstruction class, which represents an instruction
for conditional branching based on a specified expression. It inherits from the Instruction class.
@param lineNumber An integer representing the line number in the code where this instruction occurs.
It helps with debugging and tracing execution flow.
@param expression A constant reference to a string representing the conditional expression associated with the
if statement. This expression determines whether the code after this should be executed or the second code after
this based on its evaluation.


## void Execute(vector<Register>& registers, vector<Instruction*>& instructions, int& instructionIndex) override
****

This function is a virtual method intended to execute a specific instruction within a sequence of instructions.
It operates on a set of registers and a list of instruction objects, moving through the instructions based on
the provided instruction index.
@param registers A reference to a vector of Register objects representing the computer's registers.
These registers hold data that the instructions may operate on or modify.
@param instructions A reference to a vector of pointers to Instruction objects.
These represent the sequence of instructions to be executed.
@param instructionIndex A reference to an integer representing the current index of the instruction to be
executed within the instructions vector. This index will be updated to point to the next instruction to
execute after this function call.


## enum InstructionType { NoType, Print, Let, If, Goto, Read }
****

Enum representing different types of instructions.


## class Instruction {

protected:
    int lineNumber = -1
****

The base abstract instruction class for other specific instructions for the program interpreter.


## Instruction(int lineNumber_, const string& expression_, InstructionType instructionType = NoType)
****

Initialize the instruction with the given base values.
@param lineNumber_ The line number of the instruction.
@param expression_ The expression argument of the instruction.
@param instructionType The type of the instruction.


## int getLineNumber() const
****

Get the line number of the instruction
@return The line number of the instruction.


## string getInstructionTypeStr() const
****

Get the string representation of the instruction type.
@return The string representation of the instruction type.


## InstructionType getInstructionType() const
****

Get the type of the instruction.
@return The type of the instruction.


## string getExpression() const
****

Get the expression argument of the instruction.
@return The expression argument of the instruction.


## virtual void Execute(vector<Register>& registers, vector<Instruction*>& instructions, int& instructionIndex) = 0
****

This function must be implemented by derived classes to execute the specific
behavior associated with the instruction.
@param registers The array of registers.
@param instructions The array of instructions.
@param instructionIndex The current instruction index.


## friend std::ostream& operator<<(std::ostream& os, const Instruction& inst)
****

Overloaded stream insertion operator for printing Instruction objects.
@param os The output stream.
@param inst The Instruction object to be printed.
@return A reference to the output stream.


## static bool isNumber(const string &str)
****

Check if a string represents a valid number.
@param str The string to be checked.
@return True if the string represents a number, false otherwise.


## virtual ~Instruction() = default
****

Destroys the Instruction object.


## string ProcessExpression(string &argument, vector<Register> &registers)
****

Process the expression. Splits the expression into tokens based of the allowed operators. Assigns the value
to the register if there is an assigning operator in the expression. Returns the registers value if needed, or
just a decimal value after evaluation.
@param argument The argument to be processed.
@param registers The array of registers.
@return The evaluated expression.


## LetInstruction(int lineNumber, const string& expression)
****

This constructor initializes a new instance of the LetInstruction class, which represents an instruction
for assigning a value to a variable. It inherits from the Instruction class.
@param lineNumber An integer representing the line number in the code where this instruction occurs.
It helps with debugging and tracing execution flow.
@param expression A constant reference to a string representing any expression associated with the assignment
operation. This could be the variable name and the value to assign, or more complex expressions involving
variables and constants.


## void Execute(vector<Register>& registers, vector<Instruction*>& instructions, int& instructionIndex) override
****

This function is a virtual method intended to execute a specific instruction within a sequence of instructions.
It operates on a set of registers and a list of instruction objects, moving through the instructions based on
the provided instruction index.
@param registers A reference to a vector of Register objects representing the computer's registers.
These registers hold data that the instructions may operate on or modify.
@param instructions A reference to a vector of pointers to Instruction objects.
These represent the sequence of instructions to be executed.
@param instructionIndex A reference to an integer representing the current index of the instruction to be
executed within the instructions vector. This index will be updated to point to the next instruction to
execute after this function call.


## class ListCommand : public Command{
public:
    // == Constructor ==
    /**
     * Constructs a ListCommand object.
     * @param pc A reference to the Computer object.
     */
    explicit ListCommand(Computer& pc)
****

The ListCommand class represents a command that lists the instructions of the loaded program.
Inherits from the Command class.


## void operator()(const string& filename, bool& active) override
****

Executes the List command.
@param filename The name of the file. (Unused)
@param active A boolean reference indicating whether the interface is active.


## class LoadCommand : public Command{
public:
    // == Constructor ==
    /**
     * Constructs a LoadCommand object.
     * @param pc A reference to the Computer object.
     */
    explicit LoadCommand(Computer& pc)
****

The LoadCommand class represents a command to load the program from a file.
Inherits from the Command class.


## void operator()(const string& filename, bool& active) override
****

Executes the Load command.
@param filename The name of the file to load the program from.
@param active A boolean reference indicating whether the interface is active.


## class NewCommand : public Command{
public:
    // == Constructor ==
    /**
     * Constructs a NewCommand object.
     * @param pc A reference to the Computer object.
     */
    explicit NewCommand(Computer& pc)
****

The NewCommand represents a command to create a new project.
Inherits from the Command class.


## void operator()(const string& filename, bool& active) override
****

Executes the New command.
@param filename The name of the file. (Unused)
@param active A boolean reference indicating whether the interface is active.


## PrintInstruction(int lineNumber, const string& expression)
****

This constructor initializes a new instance of the PrintInstruction class, which represents an instruction
for printing output to the console. It inherits from the Instruction class.
@param lineNumber An integer representing the line number in the code where this instruction occurs.
It helps with debugging and tracing execution flow.
@param expression A constant reference to a string representing the content or message to be printed.
This could include variables, literals, or expressions that need to be evaluated and printed.


## void Execute(vector<Register>& registers, vector<Instruction*>& instructions, int& instructionIndex) override
****

This function is a virtual method intended to execute a specific instruction within a sequence of instructions.
It operates on a set of registers and a list of instruction objects, moving through the instructions based on
the provided instruction index.
@param registers A reference to a vector of Register objects representing the computer's registers.
These registers hold data that the instructions may operate on or modify.
@param instructions A reference to a vector of pointers to Instruction objects.
These represent the sequence of instructions to be executed.
@param instructionIndex A reference to an integer representing the current index of the instruction to be
executed within the instructions vector. This index will be updated to point to the next instruction to
execute after this function call.


## ReadInstruction(int lineNumber, const string& expression)
****

This constructor initializes a new instance of the ReadInstruction class, which represents an instruction
for reading input from the user. It inherits from the Instruction class.
@param lineNumber An integer representing the line number in the code where this instruction occurs.
It helps with debugging and tracing execution flow.
@param expression A constant reference to a string representing a possible name of a register to read the input into.


## void Execute(vector<Register>& registers, vector<Instruction*>& instructions, int& instructionIndex) override
****

This function is a virtual method intended to execute a specific instruction within a sequence of instructions.
It operates on a set of registers and a list of instruction objects, moving through the instructions based on
the provided instruction index.
@param registers A reference to a vector of Register objects representing the computer's registers.
These registers hold data that the instructions may operate on or modify.
@param instructions A reference to a vector of pointers to Instruction objects.
These represent the sequence of instructions to be executed.
@param instructionIndex A reference to an integer representing the current index of the instruction to be
executed within the instructions vector. This index will be updated to point to the next instruction to
execute after this function call.


## explicit Register(const string& name = "", float defValue = 0)
****

Creates a Register object that stores a register's name and float value
@param name Name of the register
@param defValue Value of the register


## const string& getName() const { return name
****

Get the name of the register
@return Name of the register


## float getValue() const { return value
****

Get the value of the register
@return Value of the register


## void SetValue(float newValue) { value = newValue
****

Set the value of the register
@param newValue New value of the register


## class RunCommand : public Command{
public:
    // == Constructor ==
    /**
     * Constructs a RunCommand object.
     * @param pc A reference to the Computer object.
     */
    explicit RunCommand(Computer& pc)
****

The RunCommand class represents a command to run the program on the interpreter.
Inherits from the Command class.


## void operator()(const string& filename, bool& active) override
****

Executes the Run command.
@param filename The name of the file to be executed on.
@param active A boolean reference indicating whether the interface is active.


## class SaveCommand : public Command {
public:
    // == Constructor ==
    /**
     * Constructs a SaveCommand object.
     * @param pc A reference to the Computer object.
     */
    explicit SaveCommand(Computer& pc)
****

The SaveCommand class represents a command to save the program to a file.
Inherits from the Command class.


## void operator()(const std::string& filename, bool& active) override
****

Executes the Save command.
@param filename The name of the file to save the program to.
@param active A boolean reference indicating whether the interface is active.


## class SyntaxError : public UniqueError {
public:
    /**
     * Constructs a SyntaxError object with the given error message and optional line number.
     * @param message The error message describing the syntax issue encountered.
     * @param lineNumber The line number in the source code where the syntax error occurred. Default is -1.
     */
    explicit SyntaxError(const std::string& message, int lineNumber = -1)
****

@brief Represents an error related to syntax in code.

The SyntaxError class is derived from the UniqueError class and is used to represent errors
caused by syntax issues in code.

This class inherits the message and line number information from its base class UniqueError,
and adds the specific error type "Syntax error".


## class UniqueError : public std::exception {
protected:
    string errormessage
****

@brief Represents a unique error condition.

The UniqueError class is derived from the std::exception class and serves as a base class for defining
unique error types. It encapsulates an error message, an error type, and optionally, a line number.

This class allows for the creation of custom error types with specific error messages and types.


## explicit UniqueError(const std::string& message, int lineNumber = -1, const std::string& type = "Error")
****

Constructs a UniqueError object with the given error message, optional line number, and error type.
@param message The error message describing the error condition.
@param lineNumber The line number in the source code where the error occurred. Default is -1.
@param type The type or category of the error. Default is "Error".


## char const* what() const throw() override
****

This function overrides the std::exception::what() method to provide a C-style character string
describing the error condition.
@return A character string describing the error.


