#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "calendar.h"
#include "reminder.h"
#include "string.h"

#define KEY_ESCAPE 27

#define NUM_MONTHS 12
#define BASE_YEAR 1900
#define MONTH_NAMES {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}
#define DAYS_IN_MONTH {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
#define REMINDER_PATH "REMINDER.txt"

Reminder reminders[MAX_REMINDERS];
int num_reminders = 0;


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
        case 'r':
            {            
                char reminder[MAX_REMINDER_LENGTH];
                printf("Enter reminder: ");
                fgets(reminder, MAX_REMINDER_LENGTH, stdin);

                if (strlen(reminder) == 0)
                {
                    printf("Cancelled.\n");
                    break;
                }

                createReminder(reminders, &num_reminders, reminder, *selected_day, *current_page, *selected_year);
                saveReminders(reminders, num_reminders, REMINDER_PATH);
            }
            break;
        default:
            break;
    }
}

int main() {
    const char *months[] = MONTH_NAMES;
    const int days_in_month[] = DAYS_IN_MONTH;

    if(loadReminders(reminders, &num_reminders, REMINDER_PATH) == 0) {
        printf("Error loading reminders.\n");

        printf("generate clean file? [y/n]\n");
        char c = getch();

        if(c == 'y' || c == 'Y') {
            // delete everything in the file
            FILE *file = fopen(REMINDER_PATH, "w");
            if (file == NULL)
            {
                printf("Error opening file for writing.\n");
                return 0;
            }
            fclose(file);
        } else {
            return 1;
        }
    }

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
        printf("\nReminder for %s %d:\n", months[current_page], selected_day);
        viewReminder(reminders, num_reminders, selected_day, current_page, selected_year);
        printf("\nPress [ESC] to exit.\n");

        user_input = getch();
        handleInput(user_input, &current_page, &selected_day, &selected_year, days_in_month, NUM_MONTHS);
        clearScreen();
    } while (user_input != KEY_ESCAPE);

    return 0;
}