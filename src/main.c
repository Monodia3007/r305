#include <stdio.h>
#include <getopt.h>
#include "test/no_ram_for_you.h"
#include "tp1/queue_and_stack_operations.h"
#include "tp2/archiver.h"
#include "tp2/unarchiver.h"
#include "tp3/ls.h"
#include "tp4_5/shell.h"
#include "tp6/encoder.h"
#include "tp6/decoder.h"
#include "tp6/modif_bmp.h"

/**
 * @file main.c
 *
 * @brief Main function for the program
 */
int main(int const argc, char *argv[])
{
    int c;
    while (1)
    {
        static struct option long_options[] = {
                {"infinite_malloc",            no_argument,       0, 'a'},
                {"infinite_fork",              no_argument,       0, 'c'},
                {"queue_and_stack_operations", no_argument,       0, 'd'},
                {"archiver",                   required_argument, 0, 'e'},
                {"unarchiver",                 required_argument, 0, 'f'},
                {"ls",                         required_argument, 0, 'g'},
                {"shell",                      no_argument,       0, 'h'},
                {"encoder",                    optional_argument, 0, 'j'},
                {"decoder",                    optional_argument, 0, 'k'},
                {"modif_bmp",                  required_argument, 0, 'l'},
                {0, 0,                                            0, 0}
        };

        int option_index = 0;
        c = getopt_long(argc, argv, "acdefghjkl:?", long_options, &option_index);
        if (c == -1)
            break;

        switch (c)
        {
            case 'a':
                run_infinite_malloc();
                break;

            case 'c':
                run_infinite_fork();

            case 'd':
                run_queue_and_stack_operations();
                break;

            case 'e':
                run_archiver(argc - 1, argv + 1);
                break;

            case 'f':
                run_unarchiver(argc - 1, argv + 1);
                break;

            case 'g':
                run_ls(argc - 1, argv + 1);
                break;

            case 'h':
                run_shell();
                break;

            case 'j':
                run_encodeur(argc - 1, argv + 1);
                break;

            case 'k':
                run_decodeur(argc - 1, argv + 1);
                break;

            case 'l':
                run_modif_bmp(argc - 1, argv + 1);
                break;

            default:
                printf("Invalid option\n");
                return 1;
        }
    }

    return 0;
}