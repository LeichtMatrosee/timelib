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
    printf("Kalenderwoche: %i\n", number_of_the_week(day, month, year));
    printf("Wochentag: ");
    format_day(day_of_the_week(day, month, year));

    
    return 0;
}
