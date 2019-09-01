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
        printf("\n\n \n                 _         __             \n  _______ __ _  (_)__  ___/ /_____ _  ___ \n / __/ -_)  ' \\/ / _ \\/ _  /___/  ' \\/ -_)\n/_/  \\__/_/_/_/_/_//_/\\_,_/   /_/_/_/\\__/ \n                                          \n        \n");
        //printf("===========================================================================");
        while ((input != 7))
        {
            printf("\n1. view\n2. add\n3. delete\n4. new list\n5. revert\n6. edit info\n7. exit\n");
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
                delete_from_list(fp);
                break;

            case 4:
                new_list();
                break;

            case 5:
                revert_changes(fp);
                break;

            case 6:
                edit_info();
                break;

            case 7:
                return 0;

            default:
                fprintf(stderr, "Invalid input\n");
            }
        }
    }

    return 0;
}