# timelib
Timelibrary von Gerrit Koppe

| Datum      | Bearbeiter        | Version | Bemerkung           |
| :--------- | :---------------- | :------ | :------------------ |
| 29.03.2022 | Gerrit Koppe      | 1.0     | Initiales Branching |
| 29.03.2022 | Gerrit Koppe      | 1.1     | Einfügen der ersten Funktionalitäten |
| 26.04.2022 | Gerrit Koppe      | 1.2     | Einfügen weiterer Funktionalitäten |
| 26.04.2022 | Gerrit Koppe      | 2.0     | Auslagern der Funktionen in Library |
| 28.04.2022 | Gerrit Koppe      | 2.1     | Es läuft!           |
| 28.04.2022 | Gerrit Koppe      | 2.1.1     | Es läuft tatsächlich nicht... |
| 30.04.2022 | Gerrit Koppe      | 2.2     | ES LÄUFT!           |
| 10.05.2022 | Gerrit Koppe      | 3.0     | Refactored mit Strukturen |

# timelib.c
```timelib.c``` ist eine Library mit Funktionen für Datumsberechnungen. Die Funktionen werden im Folgenden beschrieben.
## Dokumentation der Funktionen

### Struktur Date
**Beschreibung**: In der Header Datei wird eine Struktur definiert, die in den Funktionen genutzt wird. Die Struktur fasst Tag, Monat und Jahr in einer Variable zusammen.

**Felder**:

- int *day*: Der Tag des Datums
- int *month*: Der Monat des Datums
- int *year*: Das Jahr des Datums

**Code**
```C
    struct Date {
        int day;
        int month;
        int year;
    }
```

### clearBuffer()
**Beschreibung**: Leert den Eingabepuffer. Kann nach jedem ```scanf()``` genutzt werden, um Eingaben, die nicht dem Datentypen entsprechen, aus dem Puffer zu löschen, da diese ansonsten das Programm kaputt machen könnten.

**Parameter**: 

- keine.

**Return**: 

- keiner.

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
**Beschreibung**: Überprüft, ob ein Jahr ein beliebiges Jahr ab 1528 ein Schaltjahr ist.

**Parameter**:

- struct *Date*: Struktur der Form 
```C
    {
        int day;
        int month;
        int year;
    }
```

**Return**:

- int 0, falls das Jahr kein Schaltjahr ist.
- int 1, falls das Jahr ein Schaltjahr ist.

**Code**
```C
int is_leapyear(struct Date date) {
    //Überprüfung, ob das Jahr valide ist (in diesem Programm überflüssig)
    if (date.year < 1528) {
        return -1;
    }

    int leapYearTrue = 0;

    if (date.year % 4 == 0) { //Jahr durch 4 teilbar
        if (date.year % 100 == 0) { //Jahr durch 4 und durch 100 teilbar
            if (date.year % 400 == 0) { //Jahr durch 4, 100 und 400
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
**Beschreibung**: Gibt die Zahl der Tage zurück, die der gegebene Monat in dem gegebenen Jahr hat. Im Fall vom Februar wird überprüft, ob das Jahr ein Schaltjahr ist und im Anschluss entweder eine 28 oder 29 returned.

**Parameter**:

- struct *Date*: Struktur der Form 
```C
    {
        int day;
        int month;
        int year;
    }
```

**Return**:

- int: Anzahl der Tage im gegebenen Monat im gegebenen Jahr.

**Code**
```C
int get_days_for_month(struct Date date) {
    //Monatsarray initialisieren
    int daysInMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    
    //Überprüfung, ob Jahr gültig ist (wann ein Jahr gültig ist aus dem Kontext anderer Funktionen erarbeitet)
    if (date.year < 1528) {
        return -1;
    }

    //Falls das Jahr ein Schaltjahr ist, den Monatsarray so mutieren, dass der Februar 29 Tage hat, ansonsten 28
    if (is_leapyear(date)) {
        daysInMonth[1] = 29;
    } else {
        daysInMonth[1] = 28;
    }
}
```

### exists_date()
**Beschreibung**: Überprüft, ob ein angegebenes Datum existiert. Dafür wird überprüft, ob das Jahr zwischen 1582 und 2400 liegt, der Monat zwischen 1 und 12 und der Tag zwischen 1 und der höchsten Tageszahl des angegebenen Monats. Dafür wird auf die Funktion ```get_days_for_month()``` zurückgegriffen.

**Parameter**:

- struct *Date*: Struktur der Form 
```C
    {
        int day;
        int month;
        int year;
    }
```

**Return**:

- int: 1, falls das Datum existiert, 0, falls nicht.

**Code**
```C
int exists_date(struct Date date) {
    int existCheck = 1;

    //Jahr im angegebenen Zeitrahmen?
    if (date.year < 1582 || date.year > 2400) {
        printf("Das Jahr liegt nicht im zulassigen Bereich (1582 - 2400), bitte geben sie ein anderes Jahr ein.\n");
        existCheck = 0;
    }

    //Existiert der Monat?
    if (date.month < 1 || date.month > 12) {
        printf("Der angegebene Monat existiert nicht, bitte gegen sie einen Monat zwischen 1 und 12 ein.\n");
        existCheck = 0;
    }

    //Tag im Monat existent?
    if (date.day < 1 || date.day > get_days_for_month(date)) {
        printf("Der angegebene Tag existiert nicht, bitte geben sie einen Tag zwischen 1 und %i ein.\n", get_days_for_month(date));
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

- keine

**Return**: 

- struct *Date*: Struktur der Form 
```C
    {
        int day;
        int month;
        int year;
    }
```

**Code**
```C
struct Date input_date() {
    struct Date date;
    do {
        //Tag eingeben
        printf("Bitte geben sie den Tag ein: ");
        while (!scanf("%i", &date.day)) {
            printf("Ein Tag ist eine Zahl...\n");
            clearBuffer();
            continue;
        }

        //Monat eingeben
        printf("Bitte geben sie den Monat ein: ");
        while (!scanf("%i", &date.month)) {
            printf("Ein Monat ist eine Zahl...\n");
            clearBuffer();
            continue;
        }

        //Jahr eingeben
        printf("Bitte geben sie das Jahr ein: ");
        while (!scanf("%i", &date.year)) {
            printf("Ein Jahr ist eine Zahl...\n");
            clearBuffer();
            continue;
        }
    } while (!exists_date(date) || (exists_date(date) == -1)); //solange, bis das Datum existiert

    return date;
}
```

### day_of_the_year()
**Beschreibung**: Berechnet, der wievielte Tag eines Jahres ein angegebenes Datum ist. Hierfür wird zunächst die ```exists_date()``` Funktion aufgerufen, wodurch jedes Datum, das nicht existiert oder vor 1528 oder nach 2400 liegt, nicht überprüft wird.

**Parameter**:

- struct *Date*: Struktur der Form 
```C
    {
        int day;
        int month;
        int year;
    }
```

**Return**: 

- Int: Tagesnummer des eingegebenen Datums.

**Code**
```C
int day_of_the_year(struct Date date) {
    //Überprüfung, ob das Datum existiert
    if (!exists_date(date)) {
        return -1;
    }
    
    int dayOfYear = 0;

    //Addiere die Tage aller Monate vor dem Monat, in dem der Tag ist
    for (int i = 1; i < date.month; i++) {
        struct Date tempDate = date;
        tempDate.month = i;
        dayOfYear += get_days_for_month(tempDate);
    }

    //Addiere den Tag
    dayOfYear += date.day;

    return dayOfYear;
}
```

### day_of_the_week()
**Beschreibung**: Berechnet anhand der Datumsangaben, welcher Wochentag ein eingegebener Tag ist.

**Parameter**:

- struct *Date*: Struktur der Form 
```C
    {
        int day;
        int month;
        int year;
    }
```

**Return**:

- int: Tageszahl der Woche. 0 = Sonntag, 1 = Montag ... 6 = Samstag
  
**Code**
```C
int day_of_the_week(struct Date date) {
    int dayOfTheWeek = 0;

    if (exists_date(date)) {
        //Courtesy of Stackoverflow
        dayOfTheWeek = (date.day += date.month < 3 ? date.year-- : date.year - 2, 23*date.month/9 + date.day + 4 + date.year/4- date.year/100 + date.year/400)%7;
    }
    return dayOfTheWeek;
}
```
### number_of_the_week()
**Beschreibung**: Berechnet anhand der Datumsangaben, in der wie vielten Kalenderwoche des angegeben Jahres das Datum ist. Anfang und Ende des Jahres sollten mit Vorsicht genossen werden, da am Anfang eine 0 ausgegeben werden kann (letzte Woche des Vorjahres) und am Ende eine -1 (erste Woche des nächsten Jahres).

**Parameter**:

- struct *Date*: Struktur der Form 
```C
    {
        int day;
        int month;
        int year;
    }
```

**Return**:

- int: Kalenderwochennummer; -1, falls es die erste Woche des nächsten Jahres ist und 0, falls es die letzte Woche des Vorjahres ist.

**Code**
```C
int number_of_the_week(struct Date date) {
    int dayArray[7] = {7,1,2,3,4,5,6};

    int weekCounter = 0;
    int has53Weeks = 0;

    struct Date firstDay;
    firstDay.day = 1;
    firstDay.month = 1;
    firstDay.year = date.year;
    
    int firstDayOfYear = dayArray[day_of_the_week(firstDay)];

    struct Date lastDay;
    lastDay.day = 31;
    lastDay.month = 12;
    lastDay.year = date.year;
    //Wenn das Jahr Donnerstags beginnt oder Donnerstags aufhört, hat es 53 Wochen 
    if (firstDayOfYear == 4 || dayArray[day_of_the_week(lastDay)] == 4) {
        has53Weeks = 1;
    }
    
    //Falls der erste Tag der Woche zwischen Montag und Donnerstag liegt, liegt er in der ersten Woche
    if (firstDayOfYear < 5) {
        weekCounter = 1;
    }

    //Beginne ab der zweiten Woche zu iterieren
    int startIteratingWeeks = 9 - firstDayOfYear;

    //Wochen literally einfach hochzählen
    for (int i = startIteratingWeeks; i < day_of_the_year(date); i += 7) {
        weekCounter++;
    }

    //Falls der weekcounter 53 erreicht, wir aber keine 53 Wochen haben und der Tag zwischen Montag und Donnerstag liegt,
    //muss es die erste Woche des nächsten Jahres sein.
    if (weekCounter == 53 && day_of_the_week(date) < 4 && !has53Weeks) {
        weekCounter = -1;
    }

    return weekCounter;
}
```

### format_day()
**Beschreibung**: Gibt anhand der Nummer eines Wochentags (0-6) den entsprechenden Tag aus. 0 = Sonntag, 1 = Montag ... 6 = Samstag. Der berechnete Tag wird gedruckt und nicht zurückgegeben.

**Parameter**:

- struct *Date*: Struktur der Form 
```C
    {
        int day;
        int month;
        int year;
    }
```

**Return**: 

- keiner.

**Code**
```C
void format_day(struct Date date) {
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