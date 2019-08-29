#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"

#define FILE_NAME "reminders.csv"

void print_list(FILE *fp)
{
    printf("\n===========================================\n");
    system("(head -n 2 reminders.csv && tail -n+3 reminders.csv | sort -k1) | column -s, -t  | cat");
    // change this system() call so that reminders.csv is using FILE_NAME through use of sprintf().
    printf("===========================================\n");
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
        char date[12];
        char time[9];

        printf("\nEnter class:");
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

        fprintf(fp, "\n%s,%s,%s,%s", class, name, date, time);
        fclose(fp);
    }
}

void delete_list()
{
    char confirm[2];
    printf("Are you sure you want to remove %s? (y/n)\t", FILE_NAME);
    fgets(confirm, 2, stdin);
    if (strcmp(confirm, "y") != 0)
    {
        printf("\n%s was not deleted.", FILE_NAME);
    }
    else if (remove(FILE_NAME) == 0)
    {
        printf("\n%s was deleted.", FILE_NAME);
    }
    else
    {
        fprintf(stderr, "\nAn error occurred, the file was not deleted.");
    }
}

void delete_from_list(FILE *fp)
{
    char class_query[10];
    printf("Enter the course you want to delete from: ");
    fgets(class_query,10,stdin);
    class_query[strlen(class_query)-1] = '\0';

    char name_query[100];
    printf("Enter the assignment name: ");
    fgets(name_query,100,stdin);
    name_query[strlen(name_query)-1] = '\0';

    char cmd[1024];
    char confirm[2];

    sprintf(cmd, "grep -v '%s,%s' %s | tee backup.csv | cp backup.csv %s",class_query,name_query,FILE_NAME,FILE_NAME);

    printf("Are you sure you want to remove %s from %s? (y/n)\t",name_query,class_query );
    fgets(confirm, 2, stdin);

    if (strcmp(confirm, "y") == 0){
        system(cmd);
        printf("The entry was deleted.");
    }
    else{
        fprintf(stderr, "\nAn error occurred, the entry was not deleted.");
    }
}

void revert_changes(FILE *fp){
    char confirm[2];

    printf("Reverting to last backup will erase all current info. This is the current file state: \n");
    print_list(fp);
    printf("\nThis is the backup file state:\n\n");
    system("cat backup.csv");
    printf("\nDo you wish to continue? (y/n)\t");
    fgets(confirm, 2, stdin);

    if (strcmp(confirm, "y") == 0){
        system("cp backup.csv reminders.csv");   
    }
    else{
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
    else if ((fp =fopen(FILE_NAME, "w+")) != NULL)
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
