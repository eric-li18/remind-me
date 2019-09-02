#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
#define FILE_NAME "reminders.csv"
#define USER_INFO "user_info.txt"

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
        fprintf(stderr, "Cannot open reminders list.\n");
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

            FILE *fp2;
            sprintf(command, "grep 'Phone:' %s", USER_INFO);
            fp2 = popen(command, "r");

            fgets(buf, 100, fp2);
            char phone[100];
            sscanf(buf, "Phone:%s", phone);
            if (strcmp(phone, "") == 0)
            {
                fprintf(stderr, "Please fill in a valid phone number");
                return 1;
            }
            fclose(fp2);
            sprintf(command, "cd twilio_c_sms && sh send_text.sh %s \"%s for %s is due at %d/%d/%d, %d:%d\"", phone, name, class, time.tm_mday, time.tm_mon + 1, time.tm_year + 1900, time.tm_hour, time.tm_min);
            system(command);
            fclose(fp);
        }
    }

    return 0;
}