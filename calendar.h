#ifndef CALENDAR_H
#define CALENDAR_H

#include <time.h>

// Function declarations
void handlePageChange(int *currentPage, int change, int minPage, int maxPage);
void clearScreen();
void displayMonth(int year, int month, int days, int selected_day, struct tm *timeinfo, const char *month_name);

#endif