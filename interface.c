#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>
#include "interface.h"

#define FILE_NAME "reminders.csv"
#define COURSE_INFO "course_info.csv"
#define USER_INFO "user_info.txt"
#define USER_INFO_TMP "user_info_tmp.txt"

void print_list(FILE *fp, char name[])
{
    char print_command[100];
    sprintf(print_command, "(head -n 2 %s && tail -n+3 %s | sort -k1) | column -s, -t  | cat", name, name);
    printf("\n===========================================\n");
    system(print_command);
    printf("===========================================\n");
}

char *trim_spaces(char *str)
{
    char *end;
    while (isspace((unsigned char)*str))
    {
        str++;
    }
    if (*str == 0)
    {
        return str;
    }
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
    {
        end--;
    }
    end[1] = '\0';
    return str;
}

int check_valid_date(char date[11])
{
    int day, month, year;
    char c;

    if ((sscanf(date, "%d/%d/%d%c", &day, &month, &year, &c)) != 3)
    {
        printf("Please enter a valid date.\n");
        return 1;
    }

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
                printf("Please enter a valid date.\n");
                return 1;
            }
        }
        else
        {
            printf("Please enter a valid date.\n");
            return 1;
        }
    }
    else
    {
        printf("Please enter a valid date. \n");
        return 1;
    }
}

int check_valid_time(char time[8])
{
    int hour, minute;
    char c;
    if ((sscanf(time, "%d:%d%c", &hour, &minute, &c)) != 2)
    {
        printf("Please enter a valid time.\n");
        return 1;
    }

    if (hour >= 0 && hour <= 23)
    {
        if (minute >= 0 && minute <= 59)
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

void add_to_list(FILE *fp)
{
    if ((fp = fopen(FILE_NAME, "a")) == NULL)
    {
        fprintf(stderr, "Cannot open reminders list.\n");
    }
    else
    {
        char buf[100];
        char class[100];
        char name[100];
        char date[100];
        char time[100];
        char professor[100];
        char email[100];
        char command[100];
        int exit_code;

        printf("\nEnter class: ");
        fgets(buf, 100, stdin);
        class[strlen(buf) - 1] = '\0';
        strcpy(class, trim_spaces(buf));
        sprintf(command, "grep -q '%s' %s", class, COURSE_INFO);
        exit_code = system(command);
        if (WEXITSTATUS(exit_code) != 0)
        {
            FILE *fp2;
            if ((fp2 = fopen(COURSE_INFO, "a")) == NULL)
            {
                fprintf(stderr, "Cannot open course list.\n");
                return;
            }
            //Implementation for editing this list?
            printf("This is a new course.\n");

            printf("Enter the professor's name: ");
            fgets(buf, 100, stdin);
            class[strlen(buf) - 1] = '\0';
            strcpy(professor, trim_spaces(buf));

            printf("Enter the professor's email: ");
            fgets(buf, 100, stdin);
            class[strlen(buf) - 1] = '\0';
            strcpy(email, trim_spaces(buf));
            fprintf(fp2, "\n%s,%s,%s", class, professor, email);
            printf("The course has now been registered.\n");
            fclose(fp2);
        }

        printf("Enter assignment name: ");
        fgets(buf, 100, stdin);
        class[strlen(buf) - 1] = '\0';
        strcpy(name, trim_spaces(buf));

        sprintf(command, "grep -q '%s,%s' %s", class, name, FILE_NAME);
        exit_code = system(command);
        if (WEXITSTATUS(exit_code) == 0)
        {
            printf("%s in %s already exists.\n", name, class);
            return;
        }

        int valid_date = 1;
        while (valid_date != 0)
        {
            printf("Enter due date (dd/mm/yyyy): ");
            fgets(buf, 100, stdin);
            date[strlen(buf) - 1] = '\0';
            strcpy(date, trim_spaces(buf));
            valid_date = check_valid_date(date);
        }

        int valid_time = 1;
        while (valid_time != 0)
        {
            printf("Enter time (00:00 24h): ");
            //might change to 24h time later
            fgets(buf, 100, stdin);
            time[strlen(buf) - 1] = '\0';
            strcpy(time, trim_spaces(buf));
            valid_time = check_valid_time(time);
        }

        fprintf(fp, "%s,%s,%s,%s\n", class, name, date, time);
        fclose(fp);
    }
}

void delete_from_list()
{
    char class_query[10];
    printf("Enter the course you want to delete from: ");
    fgets(class_query, 10, stdin);
    class_query[strlen(class_query) - 1] = '\0';

    char name_query[100];
    printf("Enter the assignment name: ");
    fgets(name_query, 100, stdin);
    name_query[strlen(name_query) - 1] = '\0';

    char confirm[2];
    printf("Are you sure you want to remove %s from %s? (y/n): ", name_query, class_query);
    fgets(confirm, 2, stdin);

    if (strcmp(confirm, "y") == 0)
    {
        char cmd[1024];
        // sprintf(cmd, "grep -v '%s,%s' %s | tee backup.csv | cp backup.csv %s", class_query, name_query, FILE_NAME, FILE_NAME);
        // system(cmd);
        sprintf(cmd, "grep -v '%s,%s' %s > backup.csv", class_query, name_query, FILE_NAME);
        system(cmd);
        sprintf(cmd, "cp backup.csv %s", FILE_NAME);
        system(cmd);
        printf("The entry was deleted.\n");
    }
    else
    {
        fprintf(stderr, "\nAn error occurred, the entry was not deleted.");
    }
}

void revert_changes(FILE *fp)
{
    char confirm[2];

    printf("\nReverting to last backup will erase all current info. This is the current file state:\n");
    print_list(fp, FILE_NAME);
    printf("\nThis is the backup file state:\n");
    print_list(fp, "backup.csv");
    printf("\nDo you wish to continue? (y/n): ");
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

void new_list()
{
    printf("Creating a new list will delete all the data from the old list.\nDo you wish to continue? (y/n): ");
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
        fprintf(fp, "Course,Assignments,Due Date,Due Time\n");
        fclose(fp);
        printf("%s is now blank.\n", FILE_NAME);
    }
    else
    {
        fprintf(stderr, "\nAn error occurred, the file was not deleted.");
    }
}

void write_info(char subject[100], char subject_edit[100])
{
    char command[100];
    sprintf(command, "grep -v '%s' %s > user_info_tmp.txt", subject, USER_INFO);
    system(command);
    FILE *fp;
    if ((fp = fopen(USER_INFO_TMP, "a")) == NULL)
    {
        fprintf(stderr, "Cannot open user info.\n");
        return;
    }

    fprintf(fp, "%s%s", subject, subject_edit);
    fclose(fp);

    sprintf(command, "cp %s %s", USER_INFO_TMP, USER_INFO);
    system(command);
    sprintf(command, "rm %s", USER_INFO_TMP);
    system(command);
}

void edit_info()
{
    int input;

    while (input != 4)
    {
        printf("\nWhat would you like to edit?\n");
        printf("1. Name\n2. Phone\n3. Email\n4. Back\n");

        scanf("%d", &input);
        getchar();

        char buf[100];

        switch (input)
        {
        case 1:
            printf("Enter new name: ");
            fgets(buf, 100, stdin);
            buf[strlen(buf) - 1] = '\0';
            write_info("Name:", trim_spaces(buf));
            break;

        case 2:
            printf("Enter new phone: ");
            fgets(buf, 100, stdin);
            buf[strlen(buf) - 1] = '\0';
            write_info("Phone:", trim_spaces(buf));
            break;

        case 3:
            printf("Enter new email: ");
            fgets(buf, 100, stdin);
            buf[strlen(buf) - 1] = '\0';
            write_info("Email:", trim_spaces(buf));
            break;

        case 4:
            return;
            break;

        default:
            fprintf(stderr, "Invalid input.\n");
        }
    }
}
