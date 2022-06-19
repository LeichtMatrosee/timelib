#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timelib.h"

/**
 * @brief Leert den Eingabebuffer
 */
void clearBuffer() {
    while (getchar() != '\n') {
        continue;
    };
}

/**
 * @brief Überprüft, ob ein Jahr ein Schaltjahr ist
 * 
 * @param date {struct} Struct Objekt: 
 * {
 *      day (int),
 *      month (int),
 *      year (int)
 * } 
 * 
 * @return int 1, falls das Jahr ein Schaltjahr ist; 0, falls das Jahr kein Schaltjahr ist.
 */
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

/**
 * @brief Get the days for month object
 * 
 * @return int int Anzahl der Tage im eingegebenen Monat und -1, falls ein ungültiger Monat oder ein ungültiges
 * Jahr übergeben wurde.
 */
int get_days_for_month(struct Date date) {
    //Monatsarray initialisieren
    int daysInMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    
    //Überprüfung, ob Jahr gültig ist (wann ein Jahr gültig ist aus dem Kontext anderer Funktionen erarbeitet)
    if (date.year < 1528 || (date.month < 1 || date.month > 12)) {
        return -1;
    }

    //Falls das Jahr ein Schaltjahr ist, den Monatsarray so mutieren, dass der Februar 29 Tage hat, ansonsten 28
    if (is_leapyear(date)) {
        daysInMonth[1] = 29;
    } else {
        daysInMonth[1] = 28;
    }

    return daysInMonth[date.month - 1];
}

/**
 * @brief Überprüft, ob ein angegebenes Datum existiert (zwischen 1582 und 2400; Monat zwischen 1 und 12)
 * 
 * @param date {struct} Struct Objekt: 
 * {
 *      day (int),
 *      month (int),
 *      year (int)
 * }  
 * @return int 1, falls das Datum existiert; 0, falls das Datum nicht existiert
 */
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

/**
 * @brief Liest drei Ganzzahlwerte ein und returned diese als Date structure
 * 
 * @return struct Date 
 * {
 *      day (int),
 *      month (int),
 *      year (int)
 * } 
 */
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

/**
 * @brief Berechnet der wie vielte Tag des Jares ein eingegebenes Datum ist.
 * 
 * @param date {struct} Struct Objekt: 
 * {
 *      day (int),
 *      month (int),
 *      year (int)
 * } 
 * @return int Tag des Jahres
 */
int day_of_the_year(struct Date date) {
    //Überprüfung, ob das Datum existiert
    if (!exists_date(date)) {
        return -1;
    }
    
    int dayOfYear = 0;

    //Addiere die Tage aller Monate vor dem Monat, in dem der Tag ist

    if (get_days_for_month(date) == -1) {
        return -1;
    }
    for (int i = 1; i < date.month; i++) {
        struct Date tempDate = date;
        tempDate.month = i;
        dayOfYear += get_days_for_month(tempDate);
    }

    //Addiere den Tag
    dayOfYear += date.day;

    return dayOfYear;
}

/**
 * @brief Gibt den Wochentag eines Datums anhand von Tag, Monat und Jahr aus
 * 
 * @param date {struct} Struct Objekt: 
 * {
 *      day (int),
 *      month (int),
 *      year (int)
 * } 
 * @return int Wochentag (1=Montag, 2=Dienstag...)
 */
int day_of_the_week(struct Date date) {
    int dayOfTheWeek = 0;

    if (exists_date(date)) {
        //Courtesy of Stackoverflow https://stackoverflow.com/a/21235587
        dayOfTheWeek = (date.day += date.month < 3 ? date.year-- : date.year - 2, 23*date.month/9 + date.day + 4 + date.year/4- date.year/100 + date.year/400)%7;
    }
    return dayOfTheWeek;
}

/**
 * @brief Berechnet anhand eines Datums die Kalenderwoche. Anfang und Ende des Jahres sollten mit Vorsicht genossen werden,
 *        da am Anfang eine 0 ausgegeben werden kann (letzte Woche des Vorjahres) und am Ende eine 1 (erste Woche des nächsten Jahres).
 * 
 * @param date {struct} Struct Objekt: 
 * {
 *      day (int),
 *      month (int),
 *      year (int)
 * }  
 * @return int: Kalenderwochennummer; -1, falls es die erste Woche des nächsten Jahres ist und 0, falls es die letzte Woche des Vorjahres ist.
 */
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

/**
 * @brief gibt anhand der Nummer des Tages der Woche die korrekte Bezeichnung des Tages aus.
 * 
 * @param dayNumber Int: Nummer des Tages, der Formatiert werden soll. 0=Sonntag, 1=Montag, ... 6=Samstag.
 */
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
