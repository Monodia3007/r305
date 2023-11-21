#include "test/no_ram_for_you.h"
#include "tp1/queue_and_stack_operations.h"
#include "tp2/archiver.h"
#include "tp2/unarchiver.h"
#include "tp3/tp3.h"
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
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
    else if (strcmp(argv[1], "-tp3") == 0)
    {
        run_tp3(argc - 1, argv + 1);
    }
    else
    {
        printf("Invalid option\n");
    }

    return 0;
}