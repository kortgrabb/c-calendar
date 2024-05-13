#include "reminder.h"
#include <stdio.h>
#include <stdlib.h>

void createReminder(Reminder *reminders, int *num_reminders, const char *reminder, int day, int month, int year) {
    if (*num_reminders < MAX_REMINDERS)
    {
        Reminder new_reminder;
        snprintf(new_reminder.reminder, MAX_REMINDER_LENGTH, "%s", reminder);
        new_reminder.day = day;
        new_reminder.month = month;
        new_reminder.year = year;

        reminders[*num_reminders] = new_reminder;
        (*num_reminders)++;
    }
    else
    {
        printf("Cannot create reminder. Maximum number of reminders reached.\n");
    }
}

void viewReminder(const Reminder *reminders, int num_reminders, int day, int month, int year) {
    for (int i = 0; i < num_reminders; i++)
    {
        if (reminders[i].day == day && reminders[i].month == month && reminders[i].year == year)
        {
            printf("Reminder: %s\n", reminders[i].reminder);
            return;
        }
    }
    printf("No reminder found for %d/%d/%d\n", day, month, year);
}

void deleteReminder(Reminder *reminders, int *num_reminders, int day, int month, int year) {
    for (int i = 0; i < *num_reminders; i++)
    {
        if (reminders[i].day == day && reminders[i].month == month && reminders[i].year == year)
        {
            for (int j = i; j < *num_reminders - 1; j++)
            {
                reminders[j] = reminders[j + 1];
            }
            (*num_reminders)--;
            printf("Reminder deleted.\n");
            return;
        }
    }
    printf("No reminder found for %d/%d/%d\n", day, month, year);
}

int saveReminders(const Reminder *reminders, int num_reminders, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return 0;
    }

    for (int i = 0; i < num_reminders; i++)
    {
        fprintf(file, "%d;%d;%d;%s\n", reminders[i].day, reminders[i].month, reminders[i].year, reminders[i].reminder);
    }

    fclose(file);
    return 1;
}

int loadReminders(Reminder *reminders, int *num_reminders, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return 0;
    }

    while (!feof(file))
    {
        Reminder new_reminder;
        // allow spaces in reminder text
        if(fscanf(file, "%d;%d;%d;%[^\n]\n", &new_reminder.day, &new_reminder.month, &new_reminder.year, new_reminder.reminder)) 
        {
            reminders[*num_reminders] = new_reminder;
            (*num_reminders)++;

            if (*num_reminders >= MAX_REMINDERS)
            {
                break;
            }

            return 1;
        }
        else
        {
            return 0;
        }
    }

    fclose(file);
    return 1;
}