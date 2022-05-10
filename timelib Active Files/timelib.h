//Funktionsprototypen
struct Date {
    int day;
    int month;
    int year;
};
void clearBuffer();
int is_leapyear(struct Date date);
int get_days_for_month(struct Date date);
int exists_date(struct Date date);
struct Date input_date();
int day_of_the_year(struct Date date);
int day_of_the_week(struct Date date);
int number_of_the_week(struct Date date);
void format_day(int dayNumber);