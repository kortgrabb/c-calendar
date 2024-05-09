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

void displayMonth(const char *month, int days, int selected_day, int start_day, int current_day) {
    printf("+-----------------------------------------+\n");
    printf("|                   %s                   |\n", month);
    printf("+-----------------------------------------+\n");
    printf("| Mon | Tue | Wed | Thu | Fri | Sat | Sun |\n");
    printf("+-----+-----+-----+-----+-----+-----+-----+\n");
    
    // Leading spaces for the first startDay days
    printf("|");
    for (int i = 0; i < start_day; i++) {
        printf("%5c|", ' ');
    }

    for (int day = 1; day <= days; day++) {
        if (day == selected_day) {
            // Highlight current day with green
            printf(GREEN " %3d " RESET "|", day); // Regular day formatting
        } else if (day == current_day) {
            // Highlight current day with green
            printf(YELLOW " %3d " RESET "|", day); // Regular day formatting
        } else if (day % 7 == 0) {
            // Highlight Sundays with red
            printf(RED " %3d " RESET "|", day); // End of the week
        } else {
            printf(" %3d |", day); // Regular day formatting
        }
        // New line after a week, adjusted condition to wrap
        if ((day + start_day) % 7 == 0) {
            printf("\n");
            if (day < days) {
                // Draw separators between weeks
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
