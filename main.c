#include <stdio.h>
#include <string.h>
#include "submit.h"
#include "interface.h"

int main(int argc, char *argv[])
{
    //argv[1] - ?
    //argv[2] - ?

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
        while ((input != 7)) //continous loop to continue editting
        {
            //should probably clean this formatting up a bit
            printf("\n\n\t1. view\n\t2. add\n\t3. delete\n\t4. change\n\t5. new list\n\t6. delete list\n\t7. exit\n");
            scanf("%d", &input);
            getchar();

            switch (input)
            {
            case 1:
                print_list(fp);
                break;

            case 2:
                add_to_list(fp);
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
                //TODO
                break;

            case 7:
                return 0; //still unsure about terminations
                break;

            default:
                fprintf(stderr, "Invalid input");
            }
        }
    }

    return 0;
}