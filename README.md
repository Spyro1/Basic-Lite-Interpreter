# Prog 2 Nagyházi - BASIC interpeter
## Feladatleírás
Egy egyszerű BASIC-szerű nyelven programozható kalkulátornak egyetlen regisztere (a) és egy ciklusszámlálója (i) van. A számítási eredmények mindig az a regiszterben keletkeznek. A ciklusszámláló értékétől függően pedig feltételes ugrást lehet megvalósítani. Így igen egyszerű számítások programozhatók be. Az alábbi program például kiírja az első 5 páratlan számot.
```
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

## Program parancsok

- `let <regiszter> = <érték>`: Regiszternek értékadás. Az érték tartalmazhat matematikai alapműveleteket és zárójeleket. (`+`,`-`,`*`,`/`,`%`)
- `print <regiszter>/<string>`: Kiírja a regiszter vagy a kapott idézőjelek közé tett sztring értékét a szabványos kimenetre. A sztring tartalma kizárólag az angol abc nagy- és kisbetűit tartalmazhatja, illetve `\n`(sortörés), `\t`(tab), `\"`(idézőjel) speciális karaktereket.
- `if <feltétel>`: Feltételes elágazás. Ha a feltétel igaz, akkor végrehajtja a következő utasítást a sorban, ellenkező esetben az következő utáni utasításra ugrik a program. A feltétel tartalmazhat számokat, regisztereket, összehasonlító operátorokat, és/vagy/nem logikai kapukat és zárójeleket. (`>`,`>=`,`<`,`<=`,`==`,`!=`,`&&`,`||`,`!`)
- `goto <sorazonosító>`: Ha létezik a sorazonosító, akkor a megjlelölt sorazonosítóhoz ugrik a program. Ha nincs ilyen, akkor hibát dob az értelmező.
- `read <regiszter>`: Beolvas a szabványos bemenetről egy számot és eltárolja az éréket a regiszterben.


## BASIC interpreter - Osztálydiagram

```mermaid
classDiagram
    direction LR
%%    namespace interface{
        class IDE{
            - active: bool
            - commands[]: Command
            + IDE()
            + Run() void
            - PrintTitle() void
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
%%    }

%%    namespace interpreter{
        
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
%%  }
  
%%      IDE "1" *-- "1" Computer : contains    
    Computer "1" --* "1" IDE : contains    
    IDE "1" *-- "0..*" Command : contains
    
    Register <-- Instruction : uses
    Computer "1" *-- "0..*" Instruction : contains
    Computer "1" *-- "1..*" Register : contains

    Instruction <|-- LetInstruction
    Instruction <|-- PrintInstruction
    Instruction <|-- IfInstruction
    Instruction <|-- GotoInstruction
    Instruction <|-- ReadInstruction
    Instruction "1" *-- "1" InstructionType : defines
    
    Command <|-- HelpCommand
    Command <|-- RunCommand
    Command <|-- EndCommand
    Command <|-- ListCommand
    Command <|-- NewCommand
    Command <|-- LoadCommand
    Command <|-- SaveCommand
    
    
```

```mermaid
sequenceDiagram
    actor User
    
    loop 
    User ->> IDE: input cmdStr line
        IDE ->> Computer : Inetrpret line
    end
```
### Hátralévő feladatok
- [ ] Run után két > > -t rak valamiért
- [ ] Run -read-be karaktert írva végtelen >-t ír ki 

## Interfész parancsok

- `HELP`: Kiírja az interfész parancsait, és működésüket
- `RUN`: Futtatja a betöltött programot.
- `END`: Lezárja az aktuális interfészt (kód szerkesztő/alkalmazás).
- `LIST`: Kiírja a betöltött programot sorszám szerint növekvő sorban.
- `NEW`: Új programot hoz létre.
- `LOAD <fájlnév>`: Beolvassa fájlból a programot a kapott fájlnévvel.
- `SAVE <fájlnév>`: Elmenti a betöltött programot a megadott fájlnévvel.
