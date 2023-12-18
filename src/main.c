#include <stdio.h>
#include <getopt.h>
#include "test/no_ram_for_you.h"
#include "tp1/queue_and_stack_operations.h"
#include "tp2/archiver.h"
#include "tp2/unarchiver.h"
#include "tp3/ls.h"
#include "tp4_5/shell.h"
#include "tp6/encodeur.h"
#include "tp6/decodeur.h"

int main(int const argc, char* argv[]) {
    int c;
    while (1) {
        static struct option long_options[] = {
                {"infinite_malloc",             no_argument,       0, 'a'},
                {"infinite_fork",               no_argument,       0, 'b'},
                {"queue_and_stack_operations",  no_argument,       0, 'c'},
                {"archiver",                    required_argument, 0, 'd'},
                {"unarchiver",                  required_argument, 0, 'e'},
                {"ls",                          required_argument, 0, 'f'},
                {"shell",                       no_argument,       0, 'g'},
                {"encodeur",                    optional_argument, 0, 'h'},
                {"decodeur",                    optional_argument, 0, 'i'},
                {0, 0, 0, 0}
        };

        int option_index = 0;
        c = getopt_long(argc, argv, "abcdefghi:?", long_options, &option_index);
        if (c == -1)
            break;

        switch (c) {
            case 'a':
                run_infinite_malloc();
                break;

            case 'b':
                run_infinite_fork();

            case 'c':
                run_queue_and_stack_operations();
                break;

            case 'd':
                run_archiver(argc - 1, argv + 1);
                break;

            case 'e':
                run_unarchiver(argc - 1, argv + 1);
                break;

            case 'f':
                run_ls(argc - 1, argv + 1);
                break;

            case 'g':
                run_shell();
                break;

            case 'h':
                run_encodeur(argc - 1, argv + 1);
                break;

            case 'i':
                run_decodeur(argc - 1, argv + 1);
                break;

            default:
                printf("Invalid option\n");
                return 1;
        }
    }

    return 0;
}