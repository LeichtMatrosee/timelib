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

void input_date(day, month, year) {

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
    int daysInMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    
    if (is_leapear(year)) {
        daysInMonth[1] = 29;
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
    if (year < 1582 || year > 2400) {
        printf("Das Jahr liegt nicht im zulässigen Bereich (1582 - 2400), bitte geben sie ein anderes Jahr ein.\n");
        existCheck = 0;
    }

    if (month < 1 || month > 12) {
        printf("Der angegebene Monat existiert nicht, bitte gegen sie einen Monat zwischen 1 und 12 ein.\n");
        existCheck = 0;
    }

    if (month < 1 || month > 12) {
        printf("Der angegebene Tag existiert nicht, bitte geben sie einen Tag zwischen 1 und %i ein.\n", get_days_for_month(month, year));
        existCheck = 0;
    }

    return existCheck;
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


    return dayOfYear;
}

int main() {
    printf("Tag des Jahres: %i\n", day_of_the_year(31, 12, 2018));
    return 0;
}
