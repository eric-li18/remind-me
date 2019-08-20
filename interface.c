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

void delete_list()
{
    char filename[100];
    printf("Enter the name of the file you want to remove: ");
    scanf("%s", filename);
    getchar();
    printf("Are you sure you want to remove %s? (y/n)", filename);
    char confirm[2];
    fgets(confirm, 2, stdin);
    if (strcmp(confirm, "y") != 0)
    {
        printf("\n%s was not deleted.", filename);
    }
    else if(remove(filename) == 0)
    {
        printf("\n%s was deleted.", filename);
    }
    else
    {
        fprintf(stderr, "\nAn error occurred, the file was not deleted.");
    }
}

void delete_from_list(FILE *fp)
{
    //TODO
}

void edit_list(FILE *fp)
{
    //TODO
}

void new_list(FILE *fp)
{
    //TODO
}
