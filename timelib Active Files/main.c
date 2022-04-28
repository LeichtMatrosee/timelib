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
#include <math.h>
#include "timelib.h"

int main() {
    int day = 0;
    int month = 0;
    int year = 0;

    //Rufe Funktionen auf
    input_date(&day, &month, &year);
    
    //Ausgabe der Berechnungen
    printf("Der %i.%i.%i ist der %i. Tag des Jahres.\n", day, month, year, day_of_the_year(day, month, year));
    printf("Kalenderwoche: %i", number_of_the_week(day, month, year));
    if (number_of_the_week(day, month, year) == 0) {
        int weekLastYear = number_of_the_week(31, 12, year - 1);
        printf(" (%i. Woche Vorjahr)\n", weekLastYear);
    } else if (number_of_the_week(day, month, year) == 1 && month == 12) {
        printf("(naechstes Jahr)");
    } else {
        printf("\n");
    }
    printf("Wochentag: ");
    format_day(day_of_the_week(day, month, year));

    
    return 0;
}
