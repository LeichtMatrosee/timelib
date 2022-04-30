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
 * @param year Eingegebenes Jahr
 * @return int 1, falls das Jahr ein Schaltjahr ist; 0, falls das Jahr kein Schaltjahr ist.
 */
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

/**
 * @brief Get the days for month object
 * 
 * @param month Eingegebener Monat
 * @param year Eingegebenes Jahr
 * @return int Anzahl der Tage im eingegebenen Monat und -1, falls ein ungültiger Monat oder ein ungültiges
 * Jahr übergeben wurde.
 */
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

/**
 * @brief Überprüft, ob das angegebene Datum existiert.
 * 
 * @param day Eingegebener Tag
 * @param month Eingegebener Monat
 * @param year Eingegebenes Jahr
 * @return int 1, falls es existiert; 0, falls es nicht existiert
 */
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
/**
 * @brief Die Funktion liest 3 Ganzzahlwerte (Integer) ein, für Tag, Monat und Jahr. Wenn das angegebene Datum 
 * ungültig ist, wird erneut eingelesen, solange bis ein gültiges Datum eingegeben wurde.
 * 
 * @param day {POINTER} Zeigt auf die Tagesvariable in der Main
 * @param month {POINTER} Zeigt auf die Monatsvariable in der Main
 * @param year {POINTER} Zeigt auf die Jahresvariable in der Main
 */
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

/**
 * @brief Berechnet, der wie vielte Tag des Jahres der angegebene Tag ist.
 * 
 * @param day Eingegebener Tag
 * @param month Eingegebener Monat
 * @param year Eingegebenes Jahr
 * @return int Ergebnis der Berechnung oder -1, falls das Datum ungültig ist.
 */
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

/**
 * @brief Gibt den Wochentag eines Datums anhand von Tag, Monat und Jahr aus
 * 
 * @param day Tag des Datums
 * @param month Monat des Datums
 * @param year Jahr des Datums
 * @return int Wochentag (1=Montag, 2=Dienstag...)
 */
int day_of_the_week(int day, int month, int year) {
    int dayOfTheWeek = 0;

    if (exists_date(day, month, year)) {
        //Courtesy of Stackoverflow
        dayOfTheWeek = (day += month < 3 ? year-- : year - 2, 23*month/9 + day + 4 + year/4- year/100 + year/400)%7;
    }
    return dayOfTheWeek;
}

/**
 * @brief Berechnet anhand eines Datums die Kalenderwoche. Anfang und Ende des Jahres sollten mit Vorsicht genossen werden,
 *        da am Anfang eine 0 ausgegeben werden kann (letzte Woche des Vorjahres) und am Ende eine 1 (erste Woche des nächsten Jahres).
 * 
 * @param day Tag des Datums
 * @param month Monat des Datums
 * @param year Jahr des Datums
 * @return int: Kalenderwochennummer; -1, falls es die erste Woche des nächsten Jahres ist und 0, falls es die letzte Woche des Vorjahres ist.
 */
int number_of_the_week(int day, int month, int year) {
    int dayArray[7] = {7,1,2,3,4,5,6};
    int firstDayOfYear = dayArray[day_of_the_week(1,1,year)];
    int weekCounter = 0;
    int has53Weeks = 0;

    //Wenn das Jahr Donnerstags beginnt oder Donnerstags aufhört, hat es 53 Wochen 
    if (firstDayOfYear == 4 || dayArray[day_of_the_week(31,12,year)] == 4) {
        has53Weeks = 1;
    }
    
    //Falls der erste Tag der Woche zwischen Montag und Donnerstag liegt, liegt er in der ersten Woche
    if (firstDayOfYear < 5) {
        weekCounter = 1;
    }

    //Beginne ab der zweiten Woche zu iterieren
    int startIteratingWeeks = 9 - firstDayOfYear;

    //Wochen literally einfach hochzählen
    for (int i = startIteratingWeeks; i < day_of_the_year(day, month, year); i += 7) {
        weekCounter++;
    }

    //Falls der weekcounter 52 erreicht, wir aber keine 53 Wochen haben und der Tag zwischen Montag und Donnerstag liegt,
    //muss es die erste Woche des nächsten Jahres sein.
    if (weekCounter == 53 && day_of_the_week(day, month, year) < 4 && !has53Weeks) {
        weekCounter = -1;
    }

    return weekCounter;
}

/**
 * @brief gibt anhand der Nummer des Tages der Woche die korrekte Bezeichnung des Tages aus.
 * 
 * @param dayNumber 
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
