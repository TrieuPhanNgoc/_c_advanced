#include "date.h"

Date date_update(Date today)
{
    Date tomorrow;
    if (today.day != number_of_days(today))
        setDate(tomorrow,today.month, today.day + 1, today.year);
    else if (today.month == December)
        setDate(tomorrow, January, 1, today.year + 1);
    else
        setDate(tomorrow, today.month + 1, 1, today.year);
}

int number_of_days(Date date)
{
    return 1;
}

bool is_leap_year(Date date)
{
    return true;
}