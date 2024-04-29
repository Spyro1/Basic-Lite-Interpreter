# BASIC-lite interpreter - Skeleton

> Írta: Szenes Márton Miklós, Neptun kód: KTZRDZ, Készült: 2024. Budapest

## Tartalom

- []()

## Osztályok interfészei

### IDE
```cpp
class IDE {
public:
    /** Constructs an IDE object, initializes the IDE with default commands. */
    IDE();
    /** This function runs the IDE on the terminal, allowing users to interact with it. */
    void Run();
    /** Destroys the IDE object, cleans up resources allocated by the IDE. */
    ~IDE();
};
```
### Command
```cpp
class Command {
public:
    /** Creates a command that the user can use from the IDE */
    Command(Computer& pc, const char* cmdStr = "");
    /** Calls the Function dedicated to this command */
    virtual void operator()(const string& filename, bool& active) = 0;
    /** Checks if the given string is equal to the command */
    bool operator==(const string& commandStr);
    /** Destroys the command object. */
    virtual ~Command() = default;
};
```
### Register
```cpp
class Register {
public:
    /** Creates a Register object that stores a register's name and float value */
    explicit Register(const string& name = "", float defValue = 0);
    /** Get the name of the register */
    const string& getName() const { return name; }
    /** Get the value of the register */
    float getValue() const { return value; }
    /** Set the value of the register */
    void SetValue(float newValue) { value = newValue; }
};
```
### Instruction
```cpp
class Instruction {
public:
    /** Initialize the instruction with the given base values. */
    Instruction(int lineNumber_, const string& expression_, InstructionType instructionType = NoType);
    /** Get the line number of the instruction */
    int getLineNumber() const;
    /** Get the string representation of the instruction type. */
    string getInstructionTypeStr() const;
    /** Get the type of the instruction. */
    InstructionType getInstructionType() const;
    /** Get the expression argument of the instruction. */
    string getExpression() const;
    /** This function must be implemented by derived classes to execute the specific */
    virtual void Execute(vector<Register>& registers, vector<Instruction*>& instructions, int& instructionIndex) = 0;
    /** Overloaded stream insertion operator for printing Instruction objects. */
    friend std::ostream& operator<<(std::ostream& os, const Instruction& inst);
    /**
    virtual ~Instruction() = default;
```
### Computer

### Kivételek


## UML osztálydiagram

```mermaid
classDiagram
    direction LR
    class IDE{
        - active: bool
        - commands[]: Command
        + IDE()
        + Run() void
    }
    class Computer {
        - registers: Register[]
        - instructions: Instruction[]
        - instructionIndex: int
        + Computer()
        + getInstructionCount() int
        + ReadProgramFromFile(filename: string) void
        + NewInstruction(programLine: string) void
        + RunProgram() void
        + ClearProgram() void
        - ExecuteNextInstruction() void
    }    
    class Register{
        - name: string
        - value: float
        + Register(name: string, value: int)
        + getName() string
        + getValue() int
        + setValue(newValue: float) void
    }
    class InstructionType { 
        <<enumeration>>
        NoType, Print, Let, If, Goto, Read 
    }
    class Instruction {
        <<abstract>>
        - lineNumber: int
        - expression: string
        - instrTy: InstructionType
        + Instruction(lineNumber: int, expression: string)
        + getLineNumber() int
        + getInstructionTypeStr() string
        + getInstructionType() InstructionType
        + getExpression() string
        + Execute(registers: Register[], instructions: Instruction[], instructionIndex: int) void = 0*
        - ProcessExpression(argument: string, registers: Register[]) string
    }
    class LetInstruction{
        + LetInstruction(lineNumber: int, expression: string)
        + Execute(registers: Register[], instructions: Instruction[], instructionIndex: int) void
    }
    class PrintInstruction{
        + PrintInstruction(lineNumber: int, expression: string)
        + Execute(registers: Register[], instructions: Instruction[], instructionIndex: int) void
    }
    class GotoInstruction{
        + GotoInstruction(lineNumber: int, expression: string)
        + Execute(registers: Register[], instructions: Instruction[], instructionIndex: int) void
    }
    class IfInstruction{
        + IfInstruction(lineNumber: int, expression: string)
        + Execute(registers: Register[], instructions: Instruction[], instructionIndex: int) void
    }
    class ReadInstruction{
        + ReadInstruction(lineNumber: int, expression: string)
        + Execute(registers: Register[], instructions: Instruction[], instructionIndex: int) void
    }
    
    class Command{
        - cmdStr: string
        - pc&: Computer
        + Command(cmdStr: string, pc: Computer)
        + operator()(commandExpression: string) void = 0*
    }
    class HelpCommand{
        + HelpCommand(cmdStr: string, pc: Computer)
        + operator()(commandExpression: string) void
    }
    class RunCommand{
        + RunCommand(cmdStr: string, pc: Computer)
        + operator()(commandExpression: string) void
    }
    class EndCommand{
        + EndCommand(cmdStr: string, pc: Computer)
        + operator()(commandExpression: string) void
    }
    class ListCommand{
        + ListCommand(cmdStr: string, pc: Computer)
        + operator()(commandExpression: string) void
    }
    class NewCommand{
        + NewCommand(cmdStr: string, pc: Computer)
        + operator()(commandExpression: string) void
    }
    class LoadCommand{
        + LoadCommand(cmdStr: string, pc: Computer)
        + operator()(commandExpression: string) void
    }
    class SaveCommand{
        + SaveCommand(cmdStr: string, pc: Computer)
        + operator()(commandExpression: string) void
    }
    class UniqueError{
        - errormessage: string
        - errorType: string
        + UniqueError(messsage: string, lineNumber: int, type: string)
        + what() string
    }
    class SyntaxError{
        + SyntaxError(messsage: string, lineNumber: int)
    }    
    class CompileError{
        + CompileError(messsage: string, lineNumber: int)
    }

    UniqueError <-- IDE : catches
    
%%    IDE "1" *-- "1" Computer : contains    
    Computer "1" --* "1" IDE : contains    
    IDE "1" *-- "0..*" Command : contains

    
    Computer "1" *-- "1..*" Register : contains
    Computer "1" *-- "0..*" Instruction : contains
    Register <-- Instruction : uses

    Instruction <|-- LetInstruction
    Instruction <|-- PrintInstruction
    Instruction <|-- IfInstruction
    Instruction <|-- GotoInstruction
    Instruction <|-- ReadInstruction
    Instruction "1" *-- "1" InstructionType : defines
    
    UniqueError <|-- CompileError
    UniqueError <|-- SyntaxError

    SyntaxError <-- Instruction : throws
    CompileError <-- Instruction : throws
    UniqueError <-- Instruction : throws
    UniqueError <-- Computer : throws
    SyntaxError <-- Computer : throws
    CompileError <-- Computer : throws
    
    Command <|-- HelpCommand
    Command <|-- RunCommand
    Command <|-- EndCommand
    Command <|-- ListCommand
    Command <|-- NewCommand
    Command <|-- LoadCommand
    Command <|-- SaveCommand
```

> Írta: Szenes Márton Miklós, Neptun kód: KTZRDZ, Készült: 2024. Budapest