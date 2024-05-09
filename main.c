#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "calendar.h"

#define KEY_ESCAPE 27
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_UP 72
#define KEY_DOWN 80

int getFirstDayOfMonth(int year, int month)
{
    struct tm timeinfo = {0};
    timeinfo.tm_year = year - 1900; // Year since 1900
    timeinfo.tm_mon = month;        // Month, starting from 0
    timeinfo.tm_mday = 1;           // First day of the month
    mktime(&timeinfo);              // Normalize the tm structure
    // Adjust day of the week to make Monday the first day
    return (timeinfo.tm_wday == 0) ? 6 : timeinfo.tm_wday - 1; // Convert so that Monday is 0
}

void handleInput(int ch, int *current_page, int *selected_day, int *selected_year, const int *daysInMonth, int total_pages)
{
    switch (ch)
    {
    case KEY_LEFT:
        handlePageChange(current_page, -1, 0, total_pages - 1);
        break;
    case KEY_RIGHT:
        handlePageChange(current_page, 1, 0, total_pages - 1);
        break;
    case KEY_UP:
        (*selected_year)++;
        break;
    case KEY_DOWN:
        (*selected_year)--;
        break;
    case 'w':
        (*selected_day)--;
        if (*selected_day < 1)
        {
            *selected_day = daysInMonth[*current_page];
        }
        break;
    case 's':
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

int main()
{
    const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                            "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    const int total_pages = sizeof(months) / sizeof(months[0]);
    int current_page = 0;
    int selected_day = 1;
    int selected_year = 0;

    time_t t = time(NULL);
    struct tm *current_time = localtime(&t);

    current_page = current_time->tm_mon;          // Set current month as starting page
    selected_year = current_time->tm_year + 1900; // Year since 1900

    clearScreen();

    int ch = 0;
    do
    {
        printf("Year: %d | "
               "Day: %d\n",
               selected_year, selected_day);
        int startDay = getFirstDayOfMonth(selected_year, current_page);
        displayMonth(months[current_page], daysInMonth[current_page], selected_day, startDay, current_time->tm_mday);

        ch = getch(); // Get the actual arrow keycode

        handleInput(ch, &current_page, &selected_day, &selected_year, daysInMonth, total_pages);

        clearScreen();
    } while (ch != KEY_ESCAPE && ch != 'q' && ch != 'Q');

    printf("Exiting...\n");

    return 0;
}
