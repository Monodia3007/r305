#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "no_ram_for_you.h"

volatile int cancel = 0;

/**
 * @brief Function to confirm the execution of a potentially dangerous operation.
 *
 * This function prompts the user to type 'y' or 'yes' before proceeding. If the user does not confirm,
 * the function will return 0, otherwise it will return 1.
 *
 * @return int Returns 1 if the user confirms the execution, 0 otherwise.
 */
int confirm_execution(void)
{
    char input[4];

    printf("Are you sure you want to proceed? (y/yes to confirm): ");
    fgets(input, 4, stdin);

    if (strcmp(input, "y\n") == 0 || strcmp(input, "yes\n") == 0)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief Scans the keyboard input in a separate thread
 *
 * This function is responsible for scanning the keyboard input in a separate thread.
 * It takes a void pointer as an argument, which can be used to pass any additional
 * arguments required for the scan_key function.
 *
 * @return void
 */
void *scan_key()
{
    while (1)
    {
        char const key = getchar();
        if (key == 'q')
        {
            cancel = 1;
            return NULL;
        }
    }
}

/**
 * @brief Function to continuously allocate memory using malloc().
 *
 * This file contains the implementation of a function that continuously
 * allocates memory using malloc(). The function runs indefinitely until an
 * error occurs during the memory allocation.
 */
void run_infinite_malloc(void)
{
    if (!confirm_execution())
    {
        printf("Execution cancelled.\n");
        return;
    }

    int ram_consumed = 0;
    pthread_t tid;

    // Create a separate thread to listen for the 'q' key
    pthread_create(&tid, NULL, scan_key, NULL);

    while (!cancel)
    {
        ram_consumed += 1;
        void* ptr = malloc(1024);
        printf("%s", (char*)ptr);
        printf("%dMio\n", ram_consumed);
    }

    pthread_join(tid, NULL);  // make sure the thread ends before exiting the function
}

/**
 * @brief Function to continuously allocate memory and create new processes using fork().
 *
 * This function continuously allocates memory using malloc() and creates new processes using fork().
 * The function runs indefinitely in a while loop.
 *
 * The function does not return anything and is marked with the _Noreturn keyword.
 *
 * @note This function can quickly consume system resources and should be used with caution.
 */
_Noreturn void run_infinite_fork(void)
{
    if (!confirm_execution())
    {
        printf("Execution cancelled.\n");
        exit(0);
    }

    int ram_consumed = 0;
    while (1)
    {
        ram_consumed += 1;
        void* ptr = malloc(1024);
        int const pid = fork();
        printf("%d%s\n",pid, (char*)ptr);
        printf("%dMio\n", ram_consumed);
    }
}