#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
#define FILE_NAME "reminders.csv"

int main()
{
    char command[100];
    int exit_code;
    time_t t = time(NULL);
    struct tm time = *localtime(&t);

    sprintf(command, "grep '%d/%d/%d,%d:%d' %s", time.tm_mday, time.tm_mon + 1, time.tm_year + 1900, time.tm_hour, time.tm_min, FILE_NAME);

    FILE *fp;
    char buf[100];

    if ((fp = popen(command, "r")) == NULL)
    {
        fprintf(stderr, "Cannot open file.\n");
        return 1;
    }

    while (fgets(buf, 100, fp) != NULL)
    {
        if (strcmp(buf, "") == 0)
        {
            fclose(fp);
            return 0;
        }
        else
        {
            char class[100];
            char name[100];
            char *token;
            token = strtok(buf, ",");
            strcpy(class, token);
            token = strtok(NULL, ",");
            strcpy(name, token);

            printf("%s for %s is due at %d/%d/%d, %d:%d\n", name, class, time.tm_mday, time.tm_mon + 1, time.tm_year + 1900, time.tm_hour, time.tm_min);
            fclose(fp);
        }
    }

    return 0;
}