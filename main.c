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
        /* printf("\033[0;36m\n\n         \n\t\t    _         __             \n     _______ __ _  (_)__  ___/ /_____ _  ___ \n    / __/ -_)  ' \\/ / _ \\/ _  /___/  ' \\/ -_)\n   / /  \\__/_/_/_/_/_//_/\\_,_/   /_/_/_/\\__/ \033[0;32m v1.0.0 \n  \033[0;36m/_/\033[0m deadline monitoring and automated submission   \n");
        printf("  \033[0;36m==================================================\n"); */

        printf("\033[0;36m\n\n      ___            _         __             \n     / _ \\___ __ _  (_)__  ___/ /_____ _  ___ \n    / , _/ -_)  ' \\/ / _ \\/ _  /___/  ' \\/ -_)\n   / /| |\\__/_/_/_/_/_//_/\\_,_/   /_/_/_/\\__/  \033[0;32mv1.0.0\n  \033[0;36m/_/ |_|\033[0m deadline monitoring and automated submission      \n\033[0;36m  ====================================================\n\n");
        while (1)
        {
            printf("\033[1;36m\n1. View monitored assignments\n2. Add assignments to monitor\n3. Delete assignment from monitoring\n4. Reset monitoring list\n5. Revert to backup list\n6. Edit user info\n7. Exit program\n\033[0m");
            scanf("%d", &input);
            getchar();

            switch (input)
            {
            case 1:
                print_list(fp, "reminders.csv");
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