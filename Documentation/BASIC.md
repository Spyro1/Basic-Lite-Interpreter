# Prog 2 Nagyházi - BASIC interpeter
## Feladatleírás
Egy egyszerű BASIC-szerű nyelven programozható kalkulátornak egyetlen regisztere (a) és egy ciklusszámlálója (i) van. A számítási eredmények mindig az a regiszterben keletkeznek. A ciklusszámláló értékétől függően pedig feltételes ugrást lehet megvalósítani. Így igen egyszerű számítások programozhatók be. Az alábbi program például kiírja az első 5 páratlan számot.
```javascript
10 let a=1
20 let i=5
30 print a
40 let a=a+2
50 let i=i-1
60 if i>0
70 goto 30
```
Készítsen objektummodellt a kalkulátor működésének modellezésére! Definiáljon utasítás-objektumokat (`Instruction`), melyek egy tároló (`List<Instruction> instructions`) objektumban tárolhatók. A működtető program (`Computer`) feladata a tárolóból kivenni a soron következő utasítás-objektumot és végrehajtani azt, majd meghatározni a soron következő utasítás helyét.
Bővítse a modellt újabb utasításokkal (pl. input) és újabb regiszterekkel!
Demonstrálja a működést egy olyan programmal ami n!-t számol! n értékét olvasa be! A megoldáshoz ne használjon STL tárolót!  
Megj: nem BASIC interpretert kell írni!

## Parancsok

- `let <regiszter> = <érték>`: Regiszternek értékadás. Az érték tartalmazhat matematikai alapműveleteket. (+,-,*,/)
- `print <regiszter>`: Kiírja a regiszter értékét a szabványos kimenetre.
- `if <feltétel>`: Feltételes elágazás. Ha a feltétel igaz, akkor végrehajtja a következő utasítást a sorban, ellenkező esetben az következő utáni utasításra ugrik a program. A feltétel tartalmazhat logikai operátorokat. (>,>=,<,<=,==,!=,AND,OR,NOT)
- `goto <sorazonosító>`: Ha megtalálható, akkor a megjlelölt sorazonosítóhoz ugrik a program.
#### Tervben:
- `read <regiszter>`: Beolvassa a szabványos bemenetről egy számot és eltáro~~lja az éréket a regiszterben.

### Hátralévő feladatok
- [ ] Let Instruction kidolgozása
- [ ] Print Instruction kidolgozása
  - [x] Regsizter kiiratás
  - [x] Szöveg kiiratás
- [ ] If Instrucion kidolgozása
- [x] Goto Instruction kidolgozása
- [ ] Read Instrucition kidolgozása
- [ ] Begin...End block
- [ ] ExecuteNextInstruction megírása

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