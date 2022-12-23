#include <stdio.h>
#include "../date/date.h"

void print_reference_table(const char* format, float fahrenheit, float celsius)
{
    printf(format, fahrenheit, celsius);
}


void create_table(const char* format)
{
    int start_fahr = 0;
    int limit_fahr = 300;
    int step_fahr = 20;

    while (start_fahr <= limit_fahr)
    {
        float celcius = (5*(start_fahr - 32)/9);
        print_reference_table(format, start_fahr, celcius);
        start_fahr += step_fahr;
    }   
}

int main()
{
    Date m_day;
    
    const char* format = "%3.0f\t %3.2f \n";
    create_table(format);
}