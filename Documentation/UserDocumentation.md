# BASIC-lite interpreter - Felhasználói Dokumentáció 

## Hibakezelés - Lehetséges hibajelzések
| Hibaüzenet / Interfész üzenet                                             | Magyarázat                                               |
|---------------------------------------------------------------------------|----------------------------------------------------------|
| [Error]: Unknown error in line: #                                       | Ismeretlen eredetű hiba                                  |
| [Error]: "filename" file not found!                                       | Nem található a kívánt fájl                              |
| [Error]: Invalid input were given!                                        | Nem megfelelő bemenetet adott a felhasználó              |
| [Computer]: Ready.                                                        | A program sikeresen lefutott                             |
| [Computer]: Unrecognizable cmdStr                                         | Nem felismerhető parancs                                 |
| [Computer]: Program loaded from file.                                     | Sikeres a program beolvasása fájlból                     |
| [Computer]: Program saved to file.                                        | Sikeres a program kiírása fájlba                         |
| [Computer]: Can not save to file.                                         | Nem sikerült fájlba írni a programot                     |
| [Computer]: New program created.                                          | Új program lett létrehozva                               |
| [Syntax error]: Line identifier already exists: #                         | Új utasítás felvétele már letező sorszámmal              |
| [Syntax error]: Instruction not recognized in line: #                     | Nem létező utasítás                                      |
| [Syntax error]: Can not recognize "argument" as a goto argument in line: # | Goto nem megfelelő paraméterezése                        |
| [Syntax error]: Can not recognize "argument" as a print argument in line: # | Print nem megfelelő paraméterezése                       |
| [Syntax error]: Can not recognize "argument" as an if condition in line: # | If nem megfelelő feltétel                                |
| [Syntax error]: Wrong string literal in line: #                           | Nem megfelelő sztring szintaxis, hiányzó idézőjel        |
| [Syntax error]: Unrecognized register name "argument" in line: #          | Nem deklarált regiszter használta                        ||
| [Syntax error]: No line identifier found to jump to in line:              | Nem létező sor azonosító lett megadva goto paraméterként |
| [Syntax error]: Program shutdown due to infinite cycle!                   | A program futás közben leállt végteln ciklus miatt       |
| [Syntax error]: Missing brackets                                          | Rossz zárójelezés egy kifejezésben                       |

