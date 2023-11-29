#include <stdio.h>
#include <string.h>
#include "test/no_ram_for_you.h"
#include "tp1/queue_and_stack_operations.h"
#include "tp2/archiver.h"
#include "tp2/unarchiver.h"
#include "tp3/ls.h"
#include "tp4_5/shell.h"
#include "tp6/encodeur.h"
#include "tp6/decodeur.h"

int main(int const argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Please provide an argument to run specific module\n");
        return 1;
    }

    if (strcmp(argv[1], "-infinite_malloc") == 0)
    {
        run_infinite_malloc();
    }

    else if (strcmp(argv[1], "-infinite_fork") == 0)
    {
        run_infinite_fork();
    }

    else if (strcmp(argv[1], "-queue_and_stack_operations") == 0)
    {
        run_queue_and_stack_operations();
    }

    else if (strcmp(argv[1], "-archiver") == 0)
    {
        run_archiver(argc - 1, argv + 1);
    }

    else if (strcmp(argv[1], "-unarchiver") == 0)
    {
        run_unarchiver(argc - 1, argv + 1);
    }

    else if (strcmp(argv[1], "-ls") == 0)
    {
        run_ls(argc - 1, argv + 1);
    }

    else if (strcmp(argv[1], "-shell") == 0)
    {
        run_shell();
    }

    else if (strcmp(argv[1], "-encodeur") == 0)
    {
        run_encodeur(argc - 1, argv + 1);
    }

    else if (strcmp(argv[1], "-decodeur") == 0)
    {
        run_decodeur(argc - 1, argv + 1);
    }

    else
    {
        printf("Invalid option\n");
        return 1;
    }

    return 0;
}
