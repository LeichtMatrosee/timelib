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
    //Rufe Funktionen auf
    struct Date date = input_date();
    struct Date lastDayLastYear = {
        31, //day
        12, //month
        date.year - 1 //year

    };
    /**
    lastDayLastYear.day = 31;
    lastDayLastYear.month = 12;
    lastDayLastYear.year = date.year - 1;
    */
    struct Date firstDayNextYear = {
        1,
        1,
        date.year + 1
    };
    /**
    firstDayNextYear.day = 1;
    firstDayNextYear.month = 1;
    firstDayNextYear.year = date.year + 1;
    */

    //Ausgabe der Berechnungea
    printf("Der %i.%i.%i ist der %i. Tag des Jahres.\n", date.day, date.month, date.year, day_of_the_year(date));
    printf("Kalenderwoche: ");
    
    if (number_of_the_week(date) == 0) {
        int weekLastYear = number_of_the_week(lastDayLastYear);
        printf("%i (%i. Woche Vorjahr)\n",number_of_the_week(date), weekLastYear);
    } else if (number_of_the_week(date) == -1) {
        printf("%i (naechstes Jahr)\n", number_of_the_week(firstDayNextYear));
    } else {
        printf("%i \n", number_of_the_week(date));
    }
    printf("Wochentag: ");
    format_day(day_of_the_week(date));

    
    return 0;
}
