#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "no_ram_for_you.h"

volatile int cancel = 0;

/**
 * @brief Function to continuously allocate memory using malloc().
 *
 * This file contains the implementation of a function that continuously
 * allocates memory using malloc(). The function runs indefinitely until an
 * error occurs during the memory allocation.
 */
void *scan_key(void *arg)
{
    char key;
    while (1)
    {
        key = getchar();
        if (key == 'q')
        {
            cancel = 1;
            return NULL;
        }
    }
}

void run_infinite_malloc(void)
{
    int ram_consumed = 0;
    pthread_t tid;

    // Create a separate thread to listen for the 'q' key
    pthread_create(&tid, NULL, &scan_key, NULL);

    while (!cancel)
    {
        ram_consumed += 1;
        malloc(1024);
        printf("%dMio\n", ram_consumed);
    }

    pthread_join(tid, NULL);  // make sure the thread ends before exiting the function
}