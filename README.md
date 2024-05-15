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
    class IDE{
        - active: bool
        - commands: vector~Command*~
        + IDE()
        + Run() void
        - PrintTitle() void
        - ReadInput(line: string, commandStr: string, argumentStr: string) void
    }
    class Computer {
        - registers: map~string, float~
        - instructions: vector~Instruction*~
        - instructionIndex: int
        + Computer()
        + getInstructionCount() int
        + ReadProgramFromFile(filename: string) void
        + NewInstruction(programLine: string) void
        + RunProgram() void
        + ClearProgram() void
        + ToUpperCaseStr(str: string) string$
        - ProcessProgramLine(inputLine: string) void
        - ClearInstructions() void
        - SortInstructions() void
        - RemoveInstruction() void
        - SplitLineToTokens(inputLine: string,...) void
    %%        - SplitLineToTokens(inputLine: string, lineNumber: int, command: string, expression: string) void$
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
        + Instruction(lineNumber: int, expression: string, instrTy: InstructionType)
        + getLineNumber() int
        + getInstructionTypeStr() string
        + getInstructionType() InstructionType
        + getExpression() string
        + Execute(registers: map~string, float~, instructions: vector~Instruction~, instructionIndex: int) void = 0*
        + isNumber(str: string) bool$
        # ProcessExpression(argument: string, registers: map~string, float~) string
        # RemoveWhiteSpace(str: string) string
        # Exists(value: int) bool
        - ReplaceCharacters(inputStr: string, searched: string, replace: string) void
        - SplitAndProcessArguments(inputArg: string, registers: map~string, float~, ...) void
    %%        - SplitAndProcessArguments(inputArg: string, registers: vector~Register~, operatorIndex: int, evaluatedArg1: float, evaluatedArg2: float, operatorChars: int) void
        - FindBracketPairIndex(str: string, openPos: int, openPair: char, ClosePair: char) int
    }
    class LetInstruction{
        + LetInstruction(lineNumber: int, expression: string)
        + Execute(registers: map~string, float~, instructions: vector~Instruction~, instructionIndex: int) void
    }
    class PrintInstruction{
        + PrintInstruction(lineNumber: int, expression: string)
        + Execute(registers: map~string, float~, instructions: vector~Instruction~, instructionIndex: int) void
    }
    class GotoInstruction{
        + GotoInstruction(lineNumber: int, expression: string)
        + Execute(registers: map~string, float~, instructions: vector~Instruction~, instructionIndex: int) void
    }
    class IfInstruction{
        + IfInstruction(lineNumber: int, expression: string)
        + Execute(registers: map~string, float~, instructions: vector~Instruction~, instructionIndex: int) void
    }
    class ReadInstruction{
        + ReadInstruction(lineNumber: int, expression: string)
        + Execute(registers: map~string, float~, instructions: vector~Instruction~, instructionIndex: int) void
    }

    class Command{
        - cmdStr: string
        - pc&: Computer
        + Command(cmdStr: string, pc: Computer)
        + operator()(commandExpression: string, active&: bool) void = 0*
        + operator==(commandStr: string) bool
    }
    class HelpCommand{
        + HelpCommand(cmdStr: string, pc: Computer)
        + operator()(commandExpression: string, active&: bool) void
    }
    class RunCommand{
        + RunCommand(cmdStr: string, pc: Computer)
        + operator()(commandExpression: string, active&: bool) void
    }
    class EndCommand{
        + EndCommand(cmdStr: string, pc: Computer)
        + operator()(commandExpression: string, active&: bool) void
    }
    class ListCommand{
        + ListCommand(cmdStr: string, pc: Computer)
        + operator()(commandExpression: string, active&: bool) void
    }
    class NewCommand{
        + NewCommand(cmdStr: string, pc: Computer)
        + operator()(commandExpression: string, active&: bool) void
    }
    class LoadCommand{
        + LoadCommand(cmdStr: string, pc: Computer)
        + operator()(commandExpression: string, active&: bool) void
    }
    class SaveCommand{
        + SaveCommand(cmdStr: string, pc: Computer)
        + operator()(commandExpression: string, active&: bool) void
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


%%    UniqueError <-- IDE : catches

%%    IDE "1" *-- "1" Computer : contains    
    Computer "1" --* "1" IDE : contains
    IDE "1" *-- "0..*" Command : contains
    IDE <-- UniqueError : catches
%%    UniqueError --> IDE : catches 


%%    Instruction --> UniqueError : throws
    Instruction --> SyntaxError : throws
    UniqueError <|-- SyntaxError
    Computer --> UniqueError : throws
    Computer --> SyntaxError : throws

%%    SyntaxError --|> UniqueError

%%    Computer "1" *-- "1..*" Register : contains
    Computer "1" *-- "0..*" Instruction : contains
%%    Register <-- Instruction : uses

    Instruction "1" *-- "1" InstructionType : defines
    Instruction <|-- LetInstruction
    Instruction <|-- PrintInstruction
    Instruction <|-- IfInstruction
    Instruction <|-- GotoInstruction
    Instruction <|-- ReadInstruction
%% ----
%%    SyntaxError <-- Instruction : throws
%%    UniqueError <-- Instruction : throws
%%    UniqueError <-- Computer : throws
%%    SyntaxError <-- Computer : throws
%% ----
    Command <|-- HelpCommand
    Command <|-- RunCommand
    Command <|-- EndCommand
    Command <|-- ListCommand
    Command <|-- NewCommand
    Command <|-- LoadCommand
    Command <|-- SaveCommand
```