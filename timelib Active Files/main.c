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
    
    //Ausgabe der Berechnungea
    printf("Der %i.%i.%i ist der %i. Tag des Jahres.\n", day, month, year, day_of_the_year(day, month, year));
    printf("Kalenderwoche: ");
    
    if (number_of_the_week(day, month, year) == 0) {
        int weekLastYear = number_of_the_week(31, 12, (year - 1));
        printf("%i (%i. Woche Vorjahr)\n",number_of_the_week(day, month, year), weekLastYear);
    } else if (number_of_the_week(day, month, year) == -1) {
        printf("%i (naechstes Jahr)\n", number_of_the_week(1, 1, year + 1));
    } else {
        printf("%i \n", number_of_the_week(day, month, year));
    }
    printf("Wochentag: ");
    format_day(day_of_the_week(day, month, year));

    
    return 0;
}
