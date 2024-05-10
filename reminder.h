#ifndef REMINDER_H
#define REMINDER_H

#define MAX_REMINDERS 100
#define MAX_REMINDER_LENGTH 100

typedef struct {
    char reminder[MAX_REMINDER_LENGTH];
    int day;
    int month;
    int year;
} Reminder;

void createReminder(Reminder *reminders, int *num_reminders, const char *reminder, int day, int month, int year);
void viewReminder(const Reminder *reminders, int num_reminders, int day, int month, int year);
void deleteReminder(Reminder *reminders, int *num_reminders, int day, int month, int year);

int saveReminders(const Reminder *reminders, int num_reminders, const char *filename);
int loadReminders(Reminder *reminders, int *num_reminders, const char *filename);

#endif