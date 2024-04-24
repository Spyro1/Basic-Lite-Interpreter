# Prog 2 Nagyházi - BASIC interpeter

> Készítette: Szenes Márton - Spyro

## Programról

A program egy **BASIC**-szerű programozási nyelv butított, egyszerűsített változatát valósítja meg, továbbiakban **BASIC-lite**-nak nevezve. Biztosít a programkód írásához egy interfészt, alap parancsokat a kód szerkesztéséhez, mentéséhez, beolvasásához és futtatásához.

Az értelmező képes regiszterekben számértékeket eltárolni és azokkal műveleteket végezni, feltételes utasításokat végrehajtani, és ugrani a programkódon belül, kiírni a standard kimenetre, és olvasni a standard bementről.

## Program parancsok

- `let <regiszter> = <érték>`: Regiszternek értékadás. Az érték tartalmazhat matematikai alapműveleteket és zárójeleket. (`+`,`-`,`*`,`/`,`%`)
- `print <regiszter>/<string>`: Kiírja a regiszter vagy a kapott idézőjelek közé tett sztring értékét a szabványos kimenetre. A sztring tartalma kizárólag az angol abc nagy- és kisbetűit tartalmazhatja, illetve `\n`(sortörés), `\t`(tab), `\"`(idézőjel) speciális karaktereket.
- `if <feltétel>`: Feltételes elágazás. Ha a feltétel igaz, akkor végrehajtja a következő utasítást a sorban, ellenkező esetben az következő utáni utasításra ugrik a program. A feltétel tartalmazhat számokat, regisztereket, összehasonlító operátorokat, és/vagy/nem logikai kapukat és zárójeleket. (`>`,`>=`,`<`,`<=`,`==`,`!=`,`&&`,`||`,`!`)
- `goto <sorazonosító>`: Ha létezik a sorazonosító, akkor a megjlelölt sorazonosítóhoz ugrik a program. Ha nincs ilyen, akkor hibát dob az értelmező.
- `read <regiszter>`: Beolvas a szabványos bemenetről egy számot és eltárolja az éréket a regiszterben.

## Interfész parancsok

- `HELP`: Kiírja az interfész parancsait, és működésüket
- `RUN`: Futtatja a betöltött programot.
- `END`: Lezárja az aktuális interfészt (kód szerkesztő/alkalmazás).
- `LIST`: Kiírja a betöltött programot sorszám szerint növekvő sorban.
- `NEW`: Új programot hoz létre.
- `LOAD <fájlnév>`: Beolvassa fájlból a programot a kapott fájlnévvel.
- `SAVE <fájlnév>`: Elmenti a betöltött programot a megadott fájlnévvel.

## BASIC-lite interpreter - UML Osztálydiagram

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