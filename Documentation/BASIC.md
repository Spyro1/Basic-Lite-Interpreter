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

- `let <regiszter> = <érték>`: Regiszternek értékadás. Az érték tartalmazhat matematikai alapműveleteket és zárójeleket. (`+`,`-`,`*`,`/`)
- `print <regiszter>/<string>`: Kiírja a regiszter vagy a kapott idézőjelek közé tett sztring értékét a szabványos kimenetre. A sztring tartalma kizárólag az angol abc nagy- és kisbetűit tartalmazhatja, illetve `\n`(sortörés), `\t`(tab), `\"`(idézőjel) speciális karaktereket.
- `if <feltétel>`: Feltételes elágazás. Ha a feltétel igaz, akkor végrehajtja a következő utasítást a sorban, ellenkező esetben az következő utáni utasításra ugrik a program. A feltétel tartalmazhat számokat, regisztereket, összehasonlító operátorokat, és/vagy/nem logikai kapukat és zárójeleket. (`>`,`>=`,`<`,`<=`,`==`,`!=`,`&&`,`||`,`!`)
- `goto <sorazonosító>`: Ha létezik a sorazonosító, akkor a megjlelölt sorazonosítóhoz ugrik a program. Ha nincs ilyen, akkor hibát dob az értelmező.
- `read <regiszter>`: Beolvas a szabványos bemenetről egy számot és eltárolja az éréket a regiszterben.


## BASIC interpreter - Osztálydiagram
```mermaid
classDiagram
    direction TB
    class IDE{
      - active: bool
      + IDE()
      + Run() void
    }
    class Computer {
        - registers: List~Register~
        - instructions: List~Instruction~
        - instructionIndex: int
        + Computer(registerCount: int)
        + ReadProgramFromFile(filename: string) void
        + NewInstruction(programLine: string) void
        + RunProgram() void
        + ExecuteNextInstruction() void        
    }    
    class Register{
        - name: string
        - value: int
        + Register(name: string, value: int)
        + getName() string
        + getValue() int
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
        + Execute(registers: Vector~Register~, instructions: Vector~Instruction~, instructionIndex: int) void*
    }
    class LetInstruction
    class PrintInstruction
    class GotoInstruction
    class IfInstruction
    class ReadInstruction
    
    IDE "1" *-- "1" Computer : contains    
    Computer "1" *-- "0..*" Instruction : contains
    Computer "1" *-- "2..*" Register : contains
    InstructionType "1" --* "1" Instruction : defines
    Register <-- Instruction : uses

    Instruction <|-- LetInstruction
    Instruction <|-- PrintInstruction
    Instruction <|-- IfInstruction
    Instruction <|-- GotoInstruction
    Instruction <|-- ReadInstruction
```

### Hátralévő feladatok
- [ ] Run után két > > -t rak valamiért
- [ ] Run -read-be karaktert írva végtelen >-t ír ki 

## Interfész parancsok
A program indulásakot egy CLI-s felület fogadja a felhasználót. Itt az alábbi parancsok adhatóak ki:

- `HELP`: Kiírja az interfész parancsait, és működésüket
- `RUN`: Futtatja a betöltött programot.
- `END`: Lezárja az aktuális interfészt (kód szerkesztő/alkalmazás).
- `LIST`: Kiírja a betöltött programot sorszám szerint növekvő sorban.
- `NEW`: Új programot hoz létre.
- `LOAD <fájlnév>`: Beolvassa fájlból a programot a kapott fájlnévvel.
- `SAVE <fájlnév>`: Elmenti a betöltött programot a megadott fájlnévvel.
