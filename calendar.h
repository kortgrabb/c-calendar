#ifndef CALENDAR_H
#define CALENDAR_H

// Function declarations
void handlePageChange(int *currentPage, int change, int minPage, int maxPage);
void clearScreen();
void displayMonth(const char *month, int days, int currentDay, int startDay);

#endif