---
title: "Readme Timelibrary"
...

# timelib
Timelibrary von Gerrit Koppe

| Datum      | Bearbeiter        | Version | Bemerkung           |
| :--------- | :---------------- | :------ | :------------------ |
| 29.03.2022 | Gerrit Koppe      | 1.0     | Initiales Branching |
| 29.03.2022 | Gerrit Koppe      | 1.1     | Einfügen der ersten Funktionalitäten |
| 26.04.2022 | Gerrit Koppe      | 1.2     | Einfügen weiterer Funktionalitäten |
| 26.04.2022 | Gerrit Koppe      | 2.0     | Auslagern der Funktionen in Library |
| 28.04.2022 | Gerrit Koppe      | 2.1     | Es läuft!           |


# timelib.c
```timelib.c``` ist eine Library mit Funktionen für Datumsberechnungen. Die Funktionen werden im Folgenden beschrieben
## Dokumentation der Funktionen

### clearBuffer()
**Beschreibung**: Leert den Eingabepuffer.

**Parameter**: keine.

**Return**: keiner.

**Code**
```C
    void clearBuffer() {
        while (getchar() != '\n') {
            continue;
        };
        return 0;
    }
```

### is_leapyear()
**Beschreibung**: Überprüft, ob ein Jahr ein Schaltjahr ist.

**Parameter**:

- int *year*: Jahr, das überprüft werden soll.

**Return**:

- int 0, falls das Jahr kein Schaltjahr ist.
- int 1, falls das Jahr ein Schaltjahr ist.

**Code**
```C
    int is_leapyear(int year) {
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
    }
```

### get_days_for_month()
**Beschreibung**: Gibt die Zahl der Tage zurück, die der gegebene Monat in dem gegebenen Jahr hat. Im Fall vom Februar wird überprüft, ob das Jahr ein Schaltjahr ist.

**Parameter**:

- int *month*: Der Monat, dessen Tageszahl zurückgegeben werden soll.
- int *year*: Das Jahr, in dem der Monat überprüft werden soll.

**Return**:

- int: Anzahl der Tage im gegebenen Monat im gegebenen Jahr.

**Code**
```C
    int get_days_for_month(int month, int year) {
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
    }
```

### exists_date()
**Beschreibung**: Überprüft, ob ein angegebenes Datum existiert. Dafür wird überprüft, ob das Jahr zwischen 1582 und 2400 liegt, der Monat zwischen 1 und 12 und der Tag zwischen 1 und der höchsten Tageszahl des angegebenen Monats. Dafür wird auf die Funktion ```get_days_for_month()``` zurückgegriffen.

**Parameter**:

- int *day*: Der Tag des Datums.
- int *month*: Der Monat des Datums.
- int *year*: Das Jahr des Datums.

**Return**:

- int: 1, falls das Datum existiert, 0, falls nicht.

**Code**
```C
    int exists_date(int day, int month, int year) {
        int existCheck = 1;

        //Jahr im angegebenen Zeitrahmen?
        if (year < 1582 || year > 2400) {
            printf("Das Jahr liegt nicht im zulassigen Bereich (1582 - 2400), bitte geben sie ein anderes Jahr ein.\n");
            existCheck = 0;
        }

        //Existiert der Monat?
        if (month < 1 || month > 12) {
            printf("Der angegebene Monat existiert nicht, bitte gegen sie einen Monat zwischen 1 und 12 ein.\n");
            existCheck = 0;
        }

        //Tag im Monat existent?
        if (day < 1 || day > get_days_for_month(month, year)) {
            printf("Der angegebene Tag existiert nicht, bitte geben sie einen Tag zwischen 1 und %i ein.\n", get_days_for_month(month, year));
            existCheck = 0;
        }

        if (!existCheck) {
            printf("\n");
        }
        return existCheck;
    }
```


### input_date()
**Beschreibung**: Erlaubt dem User, ein Datum (Tag, Monat, Jahr) einzugeben und speichert die eingegebenen Werte in die Variablen, die hinter den Pointern sind.

**Parameter**:

- int *day*: Pointer auf den Tag des Datums.
- int *month*: Pointer auf den Monat des Datums.
- int *year*: Pointer auf das Jahr des Datums.

**Return**: keiner

**Code**
```C
    void input_date(int *day, int *month, int *year) {
    
        do {
            //Tag eingeben
            printf("Bitte geben sie den Tag ein: ");
            while (!scanf("%i", day)) {
                printf("Ein Tag ist eine Zahl...\n");
                clearBuffer();
                continue;
            }

            //Monat eingeben
            printf("Bitte geben sie den Monat ein: ");
            while (!scanf("%i", month)) {
                printf("Ein Monat ist eine Zahl...\n");
                clearBuffer();
                continue;
            }

            //Jahr eingeben
            printf("Bitte geben sie das Jahr ein: ");
            while (!scanf("%i", year)) {
                printf("Ein Jahr ist eine Zahl...\n");
                clearBuffer();
                continue;
            }
        } while (!exists_date(*day, *month, *year) || (exists_date(*day, *month, *year) == -1)); //solange, bis das Datum existiert

    }
```

### day_of_the_year()
**Beschreibung**: Berechnet, der wievielte Tag eines Jahres ein angegebenes Datum ist.

**Parameter**:

- int *day*: Tag des Datums.
- int *month*: Monat des Datums.
- int *year*: Jahr des Datums.

**Return**: Int: Tagesnummer des eingegebenen Datums.

**Code**
```C
    int day_of_the_year(int day, int month, int year) {
        //Überprüfung, ob das Datum existiert
        if (!exists_date(day, month, year)) {
            return -1;
        }
        
        int dayOfYear = 0;

        //Addiere die Tage aller Monate vor dem Monat, in dem der Tag ist
        for (int i = 1; i < month; i++) {
            dayOfYear += get_days_for_month(i, year);
        }

        //Addiere den Tag
        dayOfYear += day;

        return dayOfYear;
    }
```

### day_of_the_week()
**Beschreibung**: Berechnet anhand der Datumsangaben, welcher Wochentag ein eingegebener Tag ist.

**Parameter**:

- int *day*: Tag des Datums.
- int *month*: Monat des Datums.
- int *year*: Jahr des Datums.

**Return**:

- int: Tageszahl der Woche. 0 = Sonntag, 1 = Montag ... 6 = Samstag
  
**Code**
```C
    int day_of_the_week(int day, int month, int year) {
        int dayOfTheWeek = 0;

        if (exists_date(day, month, year)) {
            //Courtesy of Stackoverflow
            dayOfTheWeek = (day += month < 3 ? year-- : year - 2, 23*month/9 + day + 4 + year/4- year/100 + year/400)%7;
        }
        return dayOfTheWeek;
    }
```
### number_of_the_week()
**Beschreibung**: Berechnet anhand der Datumsangaben, in der wie vielten Kalenderwoche des angegeben Jahres das Datum ist. Anfang und Ende des Jahres sollten mit Vorsicht genossen werden, da am Anfang eine 0 ausgegeben werden kann (letzte Woche des Vorjahres) und am Ende eine 1 (erste Woche des nächsten Jahres).

**Parameter**:

- int *day*: Tag des Datums.
- int *month*: Monat des Datums.
- int *year*: Jahr des Datums.

**Return**:

- int: Kalenderwochennummer

**Code**
```C
    int number_of_the_week(int day, int month, int year) {
        int firstWeekdayOfYear = day_of_the_week(1, 1, year);
        int firstNumber;

        if (firstWeekdayOfYear < 4) {
            firstNumber = 1;
        } else {
            firstNumber = 0;
        }
        int dayOfTheYear = day_of_the_year(day, month, year);

        int weekNumber = ceil(dayOfTheYear / 7) + firstNumber;

        if (weekNumber == 53 && (day_of_the_week(day, month, year)> 0 && day_of_the_week(day, month, year) < 4)) {
            weekNumber = 1;
        } 

        return weekNumber;
    }
```

### format_day()
**Beschreibung**: Gibt anhand der Nummer eines Wochentags (0-6) den entsprechenden Tag aus. 0 = Sonntag, 1 = Montag ... 6 = Samstag 

**Parameter**:

- int *dayNumber*: Nummer des Wochentages, der ausgegeben werden soll.

**Return**: keiner.

**Code**
```C
    void format_day(int dayNumber) {
        switch (dayNumber) {
            case 0: printf("Sonntag"); break;
            case 1: printf("Montag"); break;
            case 2: printf("Dienstag"); break;
            case 3: printf("Mittwoch"); break;
            case 4: printf("Donnerstag"); break;
            case 5: printf("Freitag"); break;
            case 6: printf("Samstag"); break;
            default: printf("ungueltige Tageszahl");
        }
    }
```