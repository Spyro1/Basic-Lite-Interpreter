# Prog 2 Nagyházi - BASIC interpeter

## Parancsok

- `let <regiszter> = <érték>`: Regiszternek értékadás. Az érték tartalmazhat matematikai alapműveleteket. (+,-,*,/)
- `print <regiszter>`: Kiírja a regiszter értékét a szabványos kimenetre.
- `if <feltétel>`: Feltételes elágazás. Ha a feltétel igaz, akkor végrehajtja a következő utasítást a sorban, ellenkező esetben az következő utáni utasításra ugrik a program. A feltétel tartalmazhat logikai operátorokat. (>,>=,<,<=,==,!=,&,|,!)
- `goto <sorazonosító>`: Ha megtalálható, akkor a megjlelölt sorazonosítóhoz ugrik a program.
#### Tervben:
- `read <regiszter>`: Beolvassa a szabványos bemenetről egy számot és eltárolja az éréket a regiszterben.

```mermaid
classDiagram
    direction TB
    class List~C~{
        <<generic>>
        - first*: Node~C~
        + Count: int
        + List()
        + Add(newItem: C)
        + operator[](idx: int)
    }
    class Node { 
        + data: C
        + next*: Node~C~ 
    }
    
    class Computer {
        - registers: List~Register~
        - instructions: List~Instruction~
        - instructionIndex: int
        + Computer(registerCount: int)
        + ReadProgramFromFile(filename: string) void
        + RunProgram() void
        + ExecuteNextInstruction() void
        
    }    
    class Instruction {
        <<abstract>>
        - lineNumber: int
        - expression: string
        + Instruction(lineNumber: int, expression: string)
        + getLineNumber() int
        + Execute(registers: Register[], regCount: int, instructionIndex: int) void
    }
    class LetInstruction
    class PrintInstruction
    class GotoInstruction
%%    class AddInstruction
%%    class SubtractInstruction 
    class IfInstruction
    
    class Register{
        - name: string
        - value: int
        + Register(name: string, value: int)
        + getName() string
        + getValue() int
    }
    
    List *-- Node
    
    Computer "1" *-- "1..*" Instruction : contains
    Computer "1" *-- "1..*" Register : contains
    
    Computer o-- List : uses    
    Register --o Instruction : uses
    List --o Instruction : uses
    
    Instruction <|-- LetInstruction
    Instruction <|-- PrintInstruction
    Instruction <|-- IfInstruction
    Instruction <|-- GotoInstruction
    Instruction <|-- ReadInstruction
```