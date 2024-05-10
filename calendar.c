#include "calendar.h"
#include <stdio.h>
#include <stdlib.h>

void handlePageChange(int *currentPage, int change, int minPage, int maxPage) {
    *currentPage += change;
    if (*currentPage < minPage) {
        *currentPage = minPage;
    } else if (*currentPage > maxPage) {
        *currentPage = maxPage;
    }
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define RESET "\033[0m"

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

void displayMonth(int year, int month, int days, int selected_day, struct tm *timeinfo, const char *month_name) {
    printf("+-----------------------------------------+\n");
    printf("|                 %s %d                |\n", month_name, year);
    printf("+-----------------------------------------+\n");
    printf("| Mon | Tue | Wed | Thu | Fri | Sat | Sun |\n");
    printf("+-----+-----+-----+-----+-----+-----+-----+\n");

    int start_day = getFirstDayOfMonth(year, month);
    
    // Leading spaces for the first startDay days
    printf("|");
    for (int i = 0; i < start_day; i++) {
        printf("%5c|", ' ');
    }

    for (int day = 1; day <= days; day++) {
        if (day == selected_day) {
            // Highlight current day with green
            printf(GREEN " %3d " RESET "|", day);
        } else if (timeinfo->tm_mday == day && timeinfo->tm_mon == month && timeinfo->tm_year == year - 1900) {
            // Highlight current day with green
            printf(YELLOW " %3d " RESET "|", day);
        } else if ((day + start_day) % 7 == 0) {
            // Highlight Sundays with red
            printf(RED " %3d " RESET "|", day);
        } else {
            printf(" %3d |", day);
        }
        if ((day + start_day) % 7 == 0) {
            printf("\n");
            if (day < days) {
                printf("+-----+-----+-----+-----+-----+-----+-----+\n|");
            }
        }
    }
    
    // If the last row is not full, fill with spaces
    int remainingCells = 7 - ((days + start_day) % 7);
    if (remainingCells != 7) {
        for (int i = 0; i < remainingCells; i++) {
            printf("     |");
        }
        printf("\n");
    }
    
    // Bottom border
    printf("+-----+-----+-----+-----+-----+-----+-----+\n");
}
