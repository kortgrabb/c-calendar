#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "calendar.h"

#define KEY_ESCAPE 27

#define NUM_MONTHS 12
#define BASE_YEAR 1900
#define MONTH_NAMES {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}
#define DAYS_IN_MONTH {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}


void handleInput(int ch, int *current_page, int *selected_day, int *selected_year, const int *daysInMonth, int total_pages) {
    switch (ch)
    {
        case 'q':
            handlePageChange(current_page, -1, 0, total_pages - 1);
            break;
        case 'e':
            handlePageChange(current_page, 1, 0, total_pages - 1);
            break;
        case 'w':
            (*selected_year)++;
            break;
        case 's':
            (*selected_year)--;
            break;
        case 'a':
            (*selected_day)--;
            if (*selected_day < 1)
            {
                *selected_day = daysInMonth[*current_page];
            }
            break;
        case 'd':
            (*selected_day)++;
            if (*selected_day > daysInMonth[*current_page])
            {
                *selected_day = 1;
            }
            break;
        default:
            break;
    }
}

int main() {
    const char *months[] = MONTH_NAMES;
    const int days_in_month[] = DAYS_IN_MONTH;

    int current_page = 0;
    int selected_day = 1;
    int selected_year = 0;

    time_t t = time(NULL);
    struct tm *current_time = localtime(&t);

    current_page = current_time->tm_mon;
    selected_year = current_time->tm_year + BASE_YEAR;

    clearScreen();

    int user_input = 0;
    do {
        printf("Navigation: [Q] Previous month | [E] Next month | [W] Next year | [S] Previous year | [A] Previous day | [D] Next day\n");
        displayMonth(selected_year, current_page, days_in_month[current_page], selected_day, current_time, months[current_page]);

        user_input = getch();
        handleInput(user_input, &current_page, &selected_day, &selected_year, days_in_month, NUM_MONTHS);

        clearScreen();
    } while (user_input != KEY_ESCAPE);

    return 0;
}