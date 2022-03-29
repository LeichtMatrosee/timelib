/**
 * @file main.c
 * @author Gerrit Koppe
 * @brief 
 * @version 0.1
 * @date 2022-03-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Leert den Eingabebuffer
 * 
 * @return int 
 */
int clearBuffer() {
    while (getchar() != '\n') {
        continue;
    };
    return 0;
}
/**
 * @brief Überprüft, ob ein Jahr ein Schaltjahr ist
 * 
 * @param year Eingegebenes Jahr
 * @return int 1, falls das Jahr ein Schaltjahr ist; 0, falls das Jahr kein Schaltjahr ist.
 */
int is_leapyear(int year) {
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
    
    //Falls das Jahr ein Schaltjahr ist, den Monatsarray so mutieren, dass der Februar 29 Tage hat, ansonsten 28
    if (is_leapyear(year)) {
        daysInMonth[1] = 29;
    } else {
        daysInMonth[1] = 28;
    }

    return daysInMonth[month];
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

    printf("\n******************************************************\n");

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

    //Falls das Datum gültig ist, das bestätigen
    if (existCheck == 1) {
        printf("Das eingegebene Datum ist gueltig.\n");
    }
    printf("******************************************************\n\n");

    return existCheck;
}
/**
 * @brief Man gibt das Datum ein und macht einen Callback, ob das Datum existiert
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
    } while (!exists_date(*day, *month, *year)); //solange, bis das Datum existiert

}

/**
 * @brief Berechnet, der wie vielte Tag des Jahres der angegebene Tag ist.
 * 
 * @param day Eingegebener Tag
 * @param month Eingegebener Monat
 * @param year Eingegebenes Jahr
 * @return int Ergebnis der Berechnung
 */
int day_of_the_year(int day, int month, int year) {
    int dayOfYear;

    //Addiere die Tage aller Monate vor dem Monat, in dem der Tag ist
    for (int i = 0; i < month - 1; i++) {
        dayOfYear += get_days_for_month(i, year);
    }

    //Addiere den Tag
    dayOfYear += day;

    return dayOfYear;
}

int main() {
    int day = 0;
    int month = 0;
    int year = 0;

    //Rufe Funktionen auf
    input_date(&day, &month, &year);
    
    //Ausgabe der Berechnungen
    printf("Der %i.%i.%i ist der %i. Tag des Jahres.\n", day, month, year, day_of_the_year(day, month, year));
    return 0;
}
