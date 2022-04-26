---
title: "Readme Timelibrary"
...

# timelib
Timelibrary von Gerrit Koppe

| Datum      | Bearbeiter        | Version | Bemerkung           |
| :--------- | :---------------- | :------ | :------------------ |
| 29.03.2022 | Gerrit Koppe      | 1.0     | Initiales Branching |
| 29.03.2022 | Gerrit Koppe      | 1.1     | Einfügen der ersten Funktionalitäten |

# Dokumentation der Funktionen

## clearBuffer()
**Beschreibung**: Leert den Eingabepuffer.

**Parameter**: keine

**Return**: 

- void

**Nutzung**: Kann nach einer Usereingabe verwendet werden, um etwaige überflüssige Zeichen im Eingabepuffer zu entfernen, damit diese nicht vom nächsten scanf aufgegriffen werden.

**Code**
```C
    while (getchar() != '\n') {
        continue;
    };
    return 0;
```

## is_leapyear()
**Beschreibung**: Überprüft, ob ein Jahr ein Schaltjahr ist.

**Parameter**:

- int *year*: Jahr, das überprüft werden soll.

**Return**:

- int 0, falls das Jahr kein Schaltjahr ist.
- int 1, falls das Jahr ein Schaltjahr ist.

**Nutzung**: 

**Code**
```C
    //Überprüfung, ob das Jahr valide ist (in diesem Programm überflüssig)
    if (year < 1528) {
        return -1;
    }

    int leapYearTrue = 0;

    if (year % 4 == 0) { //Jahr durch 4 teilbar
        if (year % 100 == 0) { //Jahr durch 4 und durch 100 teilbar
            if (year % 400 == 0) { //Jahr durch 4, 100 und 400
                leapYearTrue = 1;
            } else {
                leapYearTrue = 0; //Jahr durch 4, 100 und nicht 400 teilbar
            }
        } else {
            leapYearTrue = 1; //Jahr durch 4 und nicht durch 100 teilbar
        }
    } else {
        leapYearTrue = 0; //Jahr nicht durch 4 teilbar
    }
    return leapYearTrue;
```

## get_days_for_month()
**Beschreibung**: Gibt die Zahl der Tage zurück, die der gegebene Monat in dem gegebenen Jahr hat. Im Fall vom Februar wird überprüft, ob das Jahr ein Schaltjahr ist.

**Parameter**:

- int *month*: Der Monat, dessen Tageszahl zurückgegeben werden soll.
- int *year*: Das Jahr, in dem der Monat überprüft werden soll.

**Return**:

- int: Anzahl der Tage im gegebenen Monat im gegebenen Jahr.

**Nutzung**: 

**Code**
```C
    //Monatsarray initialisieren
    int daysInMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    
    //Überprüfung, ob Jahr gültig ist (wann ein Jahr gültig ist aus dem Kontext anderer Funktionen erarbeitet)
    if (year < 1528) {
        return -1;
    }

    //Falls das Jahr ein Schaltjahr ist, den Monatsarray so mutieren, dass der Februar 29 Tage hat, ansonsten 28
    if (is_leapyear(year)) {
        daysInMonth[1] = 29;
    } else {
        daysInMonth[1] = 28;
    }

    return daysInMonth[month - 1];
```

