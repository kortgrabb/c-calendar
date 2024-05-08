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
#define RESET "\033[0m"
void displayMonth(const char *month, int days, int currentDay, int startDay) {
    // Top border
    printf("+-----------------------------------------+\n");
    
    // Month title centered within the border
    printf("|                   %s                   |\n", month);
    printf("+-----------------------------------------+\n");
    
    // Column headers
    printf("| Mon | Tue | Wed | Thu | Fri | Sat | Sun |\n");
    printf("+-----+-----+-----+-----+-----+-----+-----+\n");
    
    // Leading spaces for the first startDay days
    printf("|");
    for (int i = 0; i < startDay; i++) {
        printf("     |"); // Align with column separators
    }

    for (int day = 1; day <= days; day++) {
        if (day == currentDay) {
            // Highlight current day with green
            printf(GREEN " %3d " RESET "|", day); // Regular day formatting
        } else {
            printf(" %3d |", day); // Regular day formatting
        }
        
        // New line after a week, adjusted condition to wrap
        if ((day + startDay) % 7 == 0) {
            printf("\n");
            if (day < days) {
                // Draw separators between weeks
                printf("+-----+-----+-----+-----+-----+-----+-----+\n|");
            }
        }
    }
    
    // If the last row is not full, fill with spaces
    int remainingCells = 7 - ((days + startDay) % 7);
    if (remainingCells != 7) {
        for (int i = 0; i < remainingCells; i++) {
            printf("     |");
        }
        printf("\n");
    }
    
    // Bottom border
    printf("+-----+-----+-----+-----+-----+-----+-----+\n");
}
