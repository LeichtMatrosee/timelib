//Funktionsprototypen
struct Date {
    int day;
    int month;
    int year;
};
/**
 * @brief Leert den Eingabebuffer
 */
void clearBuffer();

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
int is_leapyear(struct Date date);

/**
 * @brief Get the days for month object
 * 
 * @return int int Anzahl der Tage im eingegebenen Monat und -1, falls ein ungültiger Monat oder ein ungültiges
 * Jahr übergeben wurde.
 */
int get_days_for_month(struct Date date);

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
int exists_date(struct Date date);

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
struct Date input_date();

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
int day_of_the_year(struct Date date);

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
int day_of_the_week(struct Date date);
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
int number_of_the_week(struct Date date);

/**
 * @brief gibt anhand der Nummer des Tages der Woche die korrekte Bezeichnung des Tages aus.
 * 
 * @param dayNumber Int: Nummer des Tages, der Formatiert werden soll. 0=Sonntag, 1=Montag, ... 6=Samstag.
 */
void format_day(int dayNumber);