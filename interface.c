#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"

void print_list(FILE *fp)
{
    printf("\n==========================================\n");
    system("(head -n 2 test.csv && tail -n+3 test.csv | sort -k1) | column -s, -t  | cat");
    printf("==========================================\n");
}

void add_to_list(FILE *fp)
{
    if ((fp = fopen("reminders.txt", "w")) == NULL)
    {
        fprintf(stderr, "Cannot open list\n");
    }
    else
    {
        char class[100];
        char name[100];
        char date[12];
        char time[9];
        getchar();

        printf("Enter class:");
        fgets(class, 100, stdin);
        class[strlen(class) - 1] = '\0';

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
