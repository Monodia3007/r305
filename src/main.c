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
#include "ctp/filtre.h"
#include "ctp/minuscule.h"
#include "ctp/processus.h"

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
                {"filtre",                     required_argument, 0, 'm'},
                {"minuscule",                  required_argument, 0, 'o'},
                {"processus",                  no_argument,       0, 'p'},
                {"help",                       no_argument,       0, '?'},
                {0, 0,                                            0, 0}
        };

        int option_index = 0;
        c = getopt_long(argc, argv, "acdefghjklmop:?", long_options, &option_index);
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

            case 'm':
                run_filtre(argc - 1, argv + 1);
                break;

            case 'o':
                run_minuscule(argc - 1, (const char **) (argv + 1));
                break;

            case 'p':
                run_processus();
                break;

            case '?':
                printf("Usage: %s [OPTION]...\n", argv[0]);
                printf("Options:\n");
                printf("\t--infinite_malloc\n");
                printf("\t--infinite_fork\n");
                printf("\t--queue_and_stack_operations\n");
                printf("\t--archiver\n");
                printf("\t--unarchiver\n");
                printf("\t--ls\n");
                printf("\t--shell\n");
                printf("\t--encoder\n");
                printf("\t--decoder\n");
                printf("\t--modif_bmp\n");
                printf("\t--filtre\n");
                printf("\t--minuscule\n");
                printf("\t--processus\n");
                printf("\t--help\n");
                break;

            default:
                printf("Invalid option\n");
                return 1;
        }
    }

    return 0;
}