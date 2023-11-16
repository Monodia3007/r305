//
// Created by Lilith on 16/11/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "no_ram_for_you.h"

void run_infinite_malloc(void) {
    int ram_consumed = 0;
    while (1)
    {
        ram_consumed += 1;
        malloc(1024);
        printf("%dMio\n", ram_consumed);
    }
}