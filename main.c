#include <stdio.h>
#include <string.h>
#include "submit.h"
#include "interface.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "use argument: edit, ..? \n");
        return 0;
        // not sure if this should returned 0 if the script is run indefinitely
        // script should be run like ./main edit
    }

    if (strcmp(argv[1], "edit") == 0)
    {
        int input;

        FILE *fp;
        while ((input != 6)) //continous loop to continue editting
        {
            //should probably clean this formatting up a bit
            printf("\n\n1. view\n2. add\n3. delete\n4. new list\n5. delete list\n6. exit\n");
            scanf("%d", &input);

            switch (input)
            {
                // case '\0':
                //     fprintf(stderr, "reading the null byte");
                //     break;

            case 1:
                if ((fp = fopen("reminders.txt", "r")) == NULL)
                {
                    fprintf(stderr, "Cannot open file\n");
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
                break;

            case 2:
                //TODO
                break;

            case 3:
                //TODO
                break;

            case 4:
                //TODO
                break;

            case 5:
                //TODO
                break;

            case 6:
                return 0; //still unsure about terminations
                break;

            default:
                fprintf(stderr, "Invalid input");
            }
        }
    }

    return 0;
}