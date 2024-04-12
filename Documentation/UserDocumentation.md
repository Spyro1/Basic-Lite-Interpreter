# BASIC-lite interpreter - Felhasználói Dokumentáció 

## Hibakezelés - Lehetséges hibajelzések
| Hibaüzenet / Interfész üzenet                                               | Magyarázat                                               |
|-----------------------------------------------------------------------------|----------------------------------------------------------|
| [Error]: Unknown error in line: #                                           | Ismeretlen eredetű hiba                                  |
| [Error]: "filename" file not found!                                         | Nem található a kívánt fájl                              |
| [Syntax error]: Line indentifier already exists: #                          | Új utasítás felvétele már letező sorszámmal              |
| [Syntax error]: Instruction not recognized in line: #                       | Nem létező utasítás                                      |
| [Syntax error]: Can not recognize "argument" as a goto argument in line: #  | Goto nem megfelelő paraméterezése                        |
| [Syntax error]: Can not recognize "argument" as a print argument in line: # | Print nem megfelelő paraméterezése                       |
| [Syntax error]: Can not recognize "argument" as an if condition in line: #  | If nem megfelelő feltétel                                |
| [Syntax error]: Wrong string literal in line: #                             | Nem megfelelő sztring szintaxis, hiányzó idézőjel        |
| [Syntax error]: Unrecognized register name in line: #                       | Nem deklarált regiszter használta                        |
| [Runtime error]: No line identifier found to jump to in line:               | Nem létező sor azonosító lett megadva goto paraméterként |
| [Runtime error]: Program shutdown due to infinite cycle!                    | A program futás közben leállt végteln ciklus miatt       |
| [Computer]: Ready.                                                          | A program sikeresen lefutott                             |
| [Computer]: Unrecognizable command                                          | Nem felismerhető parancs                                 |
| [Computer]: Program loaded from file.                                       | Sikeres a program beolvasása fájlból                     |
| [Computer]: Program saved to file.                                          | Sikeres a program kiírása fájlba                         |
| [Computer]: Can not save to file.                                           | Nem sikerült fájlba írni a programot                     |
| [Computer]: New program created.                                            | Új program lett létrehozva                               |
|                                                                             |                                                          |
|                                                                             |                                                          |