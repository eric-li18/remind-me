#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"

#define FILE_NAME "reminders.csv"

void print_list(FILE *fp)
{
    char print_command[100];
    sprintf(print_command, "(head -n 2 %s && tail -n+3 %s | sort -k1) | column -s, -t  | cat", FILE_NAME, FILE_NAME);
    printf("\n===========================================\n");
    system(print_command);
    printf("===========================================\n");
}

int check_valid_date(char date[11])
{
    int day, month, year;

    if ((sscanf(date, "%d/%d/%d", &day, &month, &year)) == EOF)
    {
        printf("Please enter a valid date.\n");
        return 1;
    };

    if (year >= 1900 && year <= 9999)
    {
        if (month >= 1 && month <= 12)
        {
            if ((day >= 1 && day <= 31) && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12))
            {
                return 0;
            }
            else if ((day >= 1 && day <= 30) && (month == 4 || month == 6 || month == 9 || month == 11))
            {
                return 0;
            }
            else if ((day >= 1 && day <= 28) && (month == 2))
            {
                return 0;
            }
            else if (day == 29 && month == 2 && (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)))
            {
                return 0;
            }
            else
            {
                printf("here 4\n");
                printf("Please enter a valid date.\n");
                return 1;
            }
        }
        else
        {
            printf("here 3\n");
            printf("Please enter a valid date.\n");
            return 1;
        }
    }
    else
    {
        printf("here 2\n");
        printf("Please enter a valid date. \n");
        return 1;
    }
}

int check_valid_time(char time[8])
{
    int hour, minute;
    char AMPM[3];
    sscanf(time, "%d:%d%s", &hour, &minute, AMPM);

    if (hour >= 1 && hour <= 12)
    {
        if (minute >= 1 && minute <= 59)
        {
            if (strcmp(AMPM, "AM") == 0 || strcmp(AMPM, "PM") == 0)
            {
                return 0;
            }
            else
            {
                printf("Please enter a valid time.\n");
                return 1;
            }
        }
        else
        {
            printf("Please enter a valid time.\n");
            return 1;
        }
    }
    else
    {
        printf("Please enter a valid time.\n");
        return 1;
    }
}

void add_to_list(FILE *fp)
{
    if ((fp = fopen(FILE_NAME, "a")) == NULL)
    {
        fprintf(stderr, "Cannot open list\n");
    }
    else
    {
        char class[100];
        char name[100];
        char date[100];
        char time[100];

        printf("\nEnter class:");
        fgets(class, 100, stdin);
        class[strlen(class) - 1] = '\0';

        printf("Enter assignment name:");
        fgets(name, 100, stdin);
        name[strlen(name) - 1] = '\0';

        int valid_date = 1;
        while (valid_date != 0)
        {
            printf("Enter due date (dd/mm/yyyy):");
            fgets(date, 100, stdin);
            date[strlen(date) - 1] = '\0';
            valid_date = check_valid_date(date);
        }

        int valid_time = 1;
        while (valid_time != 0)
        {
            printf("Enter time (00:00AM/PM):");
            fgets(time, 100, stdin);
            time[strlen(time) - 1] = '\0';
            valid_time = check_valid_time(time);
        }

        fprintf(fp, "\n%s,%s,%s,%s", class, name, date, time);
        fclose(fp);
    }
}

void delete_from_list(FILE *fp)
{
    char class_query[10];
    printf("Enter the course you want to delete from: ");
    fgets(class_query, 10, stdin);
    class_query[strlen(class_query) - 1] = '\0';

    char name_query[100];
    printf("Enter the assignment name: ");
    fgets(name_query, 100, stdin);
    name_query[strlen(name_query) - 1] = '\0';

    char cmd[1024];
    char confirm[2];

    sprintf(cmd, "grep -v '%s,%s' %s | tee backup.csv | cp backup.csv %s", class_query, name_query, FILE_NAME, FILE_NAME);

    printf("Are you sure you want to remove %s from %s? (y/n)\t", name_query, class_query);
    fgets(confirm, 2, stdin);

    if (strcmp(confirm, "y") == 0)
    {
        system(cmd);
        printf("The entry was deleted.");
    }
    else
    {
        fprintf(stderr, "\nAn error occurred, the entry was not deleted.");
    }
}

void revert_changes(FILE *fp)
{
    char confirm[2];

    printf("Reverting to last backup will erase all current info. This is the current file state: \n");
    print_list(fp);
    printf("\nThis is the backup file state:\n\n");
    system("cat backup.csv");
    printf("\nDo you wish to continue? (y/n)\t");
    fgets(confirm, 2, stdin);

    if (strcmp(confirm, "y") == 0)
    {
        system("cp backup.csv reminders.csv");
    }
    else
    {
        fprintf(stderr, "\nAn error occurred, the file was not reverted.");
    }
}

void edit_list(FILE *fp)
{
    //TODO
}

void new_list()
{
    printf("Creating a new list will delete all the data from the old list.\nDo you wish to continue? (y/n)");
    char confirm[2];
    fgets(confirm, 2, stdin);
    FILE *fp;
    if (strcmp(confirm, "y") != 0)
    {
        printf("\n%s was not deleted.", FILE_NAME);
    }
    else if ((fp = fopen(FILE_NAME, "w+")) != NULL)
    {
        printf("\n%s was deleted.\n", FILE_NAME);
        fprintf(fp, "Course,Assignments,Due Date,Due Time");
        fclose(fp);
        printf("%s is now blank.\n", FILE_NAME);
    }
    else
    {
        fprintf(stderr, "\nAn error occurred, the file was not deleted.");
    }
}
