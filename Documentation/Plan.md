# BASIC-lite interpreter - Terv

> Írta: Szenes Márton Miklós, Neptun kód: KTZRDZ

## Paraméter kiértékelése
| Prioritás | Operátor     | Magyarázat                | Kiertékelési</br>sorrend |
|-----------|--------------|---------------------------|--------------------------|
| 1         | ()           | Zárójelezés               | 2                        |
| 2         | !, -         | Egytagú operátorok        | 9                        |
| 3         | *, /         | Szorzás, osztás           | 8                        |
| 4         | +, -         | Összeadás, kivonás        | 7                        |
| 5         | <, <=, >, >= | Összehasonlítók           | 6                        |
| 6         | ==, !=       | Ekvivalencia operátorok   | 5                        |
| 7         | &&           | Logikai ÉS                | 4                        |
| 8         | \|\|         | Logikai VAGY              | 3                        |
| 9         | =            | Értékadás (jobbról balra) | 1                        |

## Hibakezelés - Lehetséges hibajelzések
