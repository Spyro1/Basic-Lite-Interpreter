# BASIC-lite interpreter - Dokumentáció

> Írta: Szenes Márton Miklós, Neptun kód: KTZRDZ, Készült: [Dátum] Budapest

---

# Tartalom

## Osztály- és függvény dokumentáció

<!-- BEGIN DOC-COMMENT ../Full Project/include/compiler/Computer.h -->

### Computer.h

#### `Computer()`

 Creates a computer object that can run a BASIC-lite program. 

#### `size_t getInstructionCount() const`

 Gives the number of instructions in the program 

**Returns**: Number of instructions

#### `void ReadProgramFromFile(const string& filename)`

 Reads the program from the given file into the 'instructions' list. 

**Parameters**:
- `filename` - The name of the file that contains the program.

#### `void NewInstruction(const string& programLine)`

 Evaluates the read character string line. If the line number is positive, then the computer adds it to the instruction list, if the number is negative, then the computer removes the corresponding instrcution with the absolute value of the given line number. 

**Parameters**:
- `programLine` - Inputted line containing the instruction: <lineNumber> <command> <argument>

#### `void RunProgram()`

 Runs the program: Executes the instructions based on the instructionIndex value which is modified according to the previous instruction. 

#### `void ClearProgram()`

 Clears the list of instructions from the program memory and resets the instruction count to 0. 

#### `friend std::ostream& operator<<(std::ostream& os, const Computer& pc)`

 Lists the instructions stored in the memory of the computer. 

**Returns**: Returns a string containing all the instructions displayed line by line.

#### `static string ToUpperCaseStr(const string &str)`

 Converts the string to upper case letters 

**Parameters**:
- `str` - Input string

**Returns**: Upper case lettered string

#### `void ProcessProgramLine(const string& inputLine)`

 Evaluates the inputed line. Seperates the input line to tokens (line number, instruction, argument), and adds the new instrcutin to the list. 

**Parameters**:
- `inputLine` - New instruction line: <id> <instruction> <parameter>

#### `static void SplitLineToTokens(const string& inputLine, int& lineNumber, string& command, string& expression)`

 Splits a line of input into tokens representing different parts of a command. 

**Parameters**:
- `inputLine` - The input line to split.
- `lineNumber` - Reference to an integer to store the line number.
- `command` - Reference to a string to store the command token.
- `expression` - Reference to a string to store the expression token.

#### `void ClearInstructions()`

 Clears all instructions stored in the computer's memory. 

#### `void SortInstructions()`

 Sorts the instructions stored in the computer's memory. 

#### `void RemoveInstruction(int lineNumber)`

 Removes an instruction with the specified line number. 

**Parameters**:
- `lineNumber` - The line number of the instruction to remove.

#### `static bool CompareInstructions(const Instruction *a, const Instruction *b)`

 Compares two instruction pointers for sorting purposes. 

**Parameters**:
- `a` - Pointer to the first instruction.
- `b` - Pointer to the second instruction.

**Returns**: True if instruction 'a' should precede instruction 'b' in sorting, false otherwise.

<!-- END DOC-COMMENT --> 

<!-- BEGIN DOC-COMMENT ../Full Project/include/compiler/Instruction.h -->

### Instruction.h

#### `enum InstructionType`

 Enum representing different types of instructions. 

#### `class Instruction`

 The base abstract instruction class for other specific instructions for the program interpreter. 

#### `Instruction(int lineNumber_, const string& expression_, InstructionType instructionType = NoType)`

 Initialize the instruction with the given base values. 

**Parameters**:
- `lineNumber_` - The line number of the instruction.
- `expression_` - The expression argument of the instruction.
- `instructionType` - The type of the instruction.

#### `int getLineNumber() const`

 Get the line number of the instruction 

**Returns**: The line number of the instruction.

#### `string getInstructionTypeStr() const`

 Get the string representation of the instruction type. 

**Returns**: The string representation of the instruction type.

#### `InstructionType getInstructionType() const`

 Get the type of the instruction. 

**Returns**: The type of the instruction.

#### `string getExpression() const`

 Get the expression argument of the instruction. 

**Returns**: The expression argument of the instruction.

#### `virtual void Execute(vector<Register>& registers, vector<Instruction*>& instructions, int& instructionIndex) = 0`

 This function must be implemented by derived classes to execute the specific behavior associated with the instruction. 

**Parameters**:
- `registers` - The array of registers.
- `instructions` - The array of instructions.
- `instructionIndex` - The current instruction index.

#### `friend std::ostream& operator<<(std::ostream& os, const Instruction& inst)`

 Overloaded stream insertion operator for printing Instruction objects. 

**Parameters**:
- `os` - The output stream.
- `inst` - The Instruction object to be printed.

**Returns**: A reference to the output stream.

#### `static bool isNumber(const string &str)`

 Check if a string represents a valid number. 

**Parameters**:
- `str` - The string to be checked.

**Returns**: True if the string represents a number, false otherwise.

#### `virtual ~Instruction() = default`

 Destroys the Instruction object. 

#### `string ProcessExpression(string &argument, vector<Register> &registers)`

 Process the expression. Splits the expression into tokens based of the allowed operators. Assigns the value to the register if there is an assigning operator in the expression. Returns the registers value if needed, or just a decimal value after evaluation. 

**Parameters**:
- `argument` - The argument to be processed.
- `registers` - The array of registers.

**Returns**: The evaluated expression.

#### `string RemoveWhiteSpace(const string& str)`

 Removes all whitespace characters from a string. 

**Parameters**:
- `str` - The input string to remove whitespace from.

**Returns**: A new string with all whitespace characters removed.

#### `static size_t FindRegisterIndex(const std::vector<Register> &registers, const string &name)`

**Finds the index of a register in a vector of registers by name.**

  

**Parameters**:
- `registers` - The vector of registers to search in.
- `name` - The name of the register to find.

**Returns**: The index of the register if found, otherwise returns nopos.

#### `static inline bool Exists(size_t value)`

 Checks if a value exists (not equal to std::string::npos). 

**Parameters**:
- `value` - The value to check for existence.

**Returns**: true if the value exists, false otherwise.

#### `void ReplaceCharacters(string &inputStr, const string &searched, const string &replace)`

 Replaces all occurrences of characters in a string with specified replacements. 

**Parameters**:
- `inputStr` - The input string where replacements are performed.
- `searched` - The characters to search for in the input string.
- `replace` - The replacements for the searched characters.

#### `void SplitAndProcessArguments(const string& inputArg, vector<Register>& registers, size_t operatorIndex, float& evaluatedArg1, float& evaluatedArg2, size_t operatorChars = 1)`

 Splits an input argument string and processes the individual arguments. 

**Parameters**:
- `inputArg` - The input argument string to split and process.
- `registers` - A vector of registers.
- `operatorIndex` - The index of the operator in the input argument.
- `evaluatedArg1` - The first evaluated argument after splitting.
- `evaluatedArg2` - The second evaluated argument after splitting.
- `operatorChars` - The number of characters representing the operator (default: 1).

#### `size_t FindBracketPairIndex(string str, size_t openPos, char OpenPair = '(', char ClosePair = ')')`

 Finds the index of the closing bracket corresponding to an opening bracket in a string. 

**Parameters**:
- `str` - The input string where to search for the bracket pair.
- `openPos` - The position of the opening bracket.
- `OpenPair` - The opening bracket character (default: '(').
- `ClosePair` - The closing bracket character (default: ')').

**Returns**: The index of the closing bracket.

<!-- END DOC-COMMENT --> 