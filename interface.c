#include <stdio.h>
#include <string.h>
#include "interface.h"

void print_list(FILE *fp)
{
    if ((fp = fopen("reminders.txt", "r")) == NULL)
    {
        fprintf(stderr, "Cannot open list\n");
        //need any termination? break? exit? return?
    }
    else
    {
        printf("\n=========================\n");
        char c;
        while ((c = getc(fp)) != EOF)
        {
            putchar(c);
        }
        fclose(fp);
        printf("\n=========================\n");
    }
}

void add_to_list(FILE *fp)
{
    if ((fp = fopen("reminders.txt", "a")) == NULL)
    {
        fprintf(stderr, "Cannot open list\n");
    }
    else
    {
        char name[100];
        char date[12];
        char time[9];
        getchar();

        printf("Enter assignment name:");
        fgets(name, 100, stdin);
        name[strlen(name) - 1] = '\0';

        printf("Enter due date (dd/mm/yyyy):");
        fgets(date, 12, stdin);
        date[strlen(date) - 1] = '\0';

        printf("Enter time (00:00AM/PM):");
        fgets(time, 9, stdin);
        date[strlen(date) - 1] = '\0';

        fprintf(fp, "\n\n%s, %s, %s", name, date, time);
        fclose(fp);
    }
}
