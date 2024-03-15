## Autópálya forgalom
Készítsen objektummodellt az autópálya forgalmának modellezésére! Egy L cellára osztott autópályán N autó van. Egy cellában csak egy autó tartózkodhat egyszerre, így L-N cella üres. Minden autónak van egy egész értékű sebessége. A szimulációt ciklusonként végezzük. Minden ciklusban minden autóra elvégezzük a következő műveleteket:

1. Ha egy autó sebessége még nem érte el a maximumot (5), akkor a sebességét eggyel megnöveljük.
2. Ha egy autó előtt levő üres cellák száma (az előtte levő autóig) kisebb, mint a sebessége, akkor az autó sebességet lecsökkentjük az előtte levő üres cellák számának megfelelő értékre.
3. Egy adott p(=0.15) valószínűséggel csökkentjük a mozgó autók sebességet eggyel. (Vezetők figyelmetlensége).
4. Minden autót előremozgatunk annyi cellával, amennyi a sebessége. 

Egyszerű karakteres kimenetet feltételezve "rajzolja ki" az autópálya állapotát egy-egy szimulációs ciklus után.
Demonstrálja a működést külön modulként fordított tesztprogrammal! A megoldáshoz ne használjon STL tárolót!


```mermaid
classDiagram
    class Car{
        - id : int
        - speed : int
        $ maxSpeed : int
        $ possibility : float
        
        + Getspeed() int
        + SetSpeed() void
        + IncreaseSpeed() void
        + RandomizeSpeed() void
    }
    class Lane{
        - carId : int
        - hasCar : bool
    }
    class Highway{
        - L : int
        - N : int
        - lane : Cell[L]
        - cars : Car[N]
        
        + Highway()
        + NextStep() void
    }
    class Cell{
        car : Car*
    }
    
    Car --* Highway
    Cell --* Highway
```
## Szerverfarm
Tervezzen objektummodellt számítógépek üzemeltetését segítő felügyeleti rendszer működésének modellezésére!
A modellben legyenek érzékelők (diszk kapacitás, memória kapacitás, processzor terheltség, szerverszoba hőmérséklet, tűzjelző, stb.), logikai kapuk (és, vagy, nem) kapcsolók, és vészcsengő! Tetszőlegesen bonyolult modell legyen felépíthető a komponensek és a logikai kapuk egyszerű összekapcsolásával!
Demonstrálja a működést külön modulként fordított tesztprogrammal! A megoldáshoz ne használjon STL tárolót!

```mermaid
classDiagram
    direction LR
    class LogicCircuit{
        - ioPorts : IO
        + LogicCircuit()
        + AddInput(Node) void
        + AddOutput(Node) void
        + AddGate(Gate) void
    }
    class Node{
        - name : string
        - value : bool
        + Node()
        + Node(name, value)
        + GetValue() bool
        + SetValue() void
    }
    class IO{
        <<abstract>>
        - numOfIn : int
        - numOfOut : int
        - inputs* : Node[]
        - outputs* : Node[]
        + IO()
        + GetNumOfIn() int
        + GetNumOfOut() int
        + Add
    }
    class LogicGate {
        <<abstract>>
        - ioPorts : IO
        + LogicGate()
        + Logic() void
    }
    class ANDGate
    class ORGate 
    class NOTGate 
    
    class NodeType{
        <<enumeration>>
        IN, OUT
    }
%%        direction TB
%%    class Sensor{
%%        - name : string
%%        - value : int
%%        + Sensor(name, value)
%%        + GetName() string
%%        + GetValue() int
%%        + SetValue() void
%%    }
%%    class DiscCapacitíy
%%    class MemoryCapacity
%%    class Cpu
%%    class Temperature
%%    class FireAlarm    
%%    class EmergencyAlarm
%%    
%%    Sensor <|--DiscCapacitíy
%%    Sensor <|-- MemoryCapacity
%%    Sensor <|-- Cpu
%%    Sensor <|--Temperature
%%    Sensor <|-- FireAlarm
%%    Sensor <|-- EmergencyAlarm
    
%%    LogicGate --* LogicCircuit
%%    LogicCircuit o-- Node
    Node --o LogicCircuit
    LogicCircuit *-- LogicGate
    LogicGate <|-- ANDGate
    LogicGate <|-- ORGate
    LogicGate <|-- NOTGate

%%    LogicGate --* IO
    IO --* LogicCircuit
    IO --* LogicGate
    Node --* IO
%%    NOTGate --* IO
%%    ANDGate --* IO
%%    ORGate --* IO
    
    
```

