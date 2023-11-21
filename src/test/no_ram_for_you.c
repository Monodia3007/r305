#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "no_ram_for_you.h"

volatile int cancel = 0;


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
    char key;
    while (1)
    {
        key = (char) getchar();
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
    int ram_consumed = 0;
    pthread_t tid;
    void* ptr;

    // Create a separate thread to listen for the 'q' key
    pthread_create(&tid, NULL, &scan_key, NULL);

    while (!cancel)
    {
        ram_consumed += 1;
        ptr = malloc(1024);
        printf("%s", (char*)ptr);
        printf("%dMio\n", ram_consumed);
    }

    pthread_join(tid, NULL);  // make sure the thread ends before exiting the function
}

void run_infinite_fork(void)
{
    int pid;

    while (1)
    {
        pid = fork();
        printf("%d\n",pid);
    }
}