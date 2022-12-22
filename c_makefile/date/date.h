#include <stdbool.h>

enum kMonth {
    January     = 1,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
};

enum kDay {
    Sunday  =   1,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Staturday
};

struct date {
    enum kMonth month;
    enum kDay   day;
    int         year;
};

typedef struct date Date;

Date date_update(Date date);
int number_of_days(Date date);
bool is_leap_year(Date date);

// Macro to set a date in a structure
#define setDate(s,mm,dd,yy) s = (Date) {mm,dd,yy}

extern Date todaysDate;