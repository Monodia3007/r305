//
// Created by Lilith on 16/11/2023.
//

#include <malloc.h>

int main(void)
{
    int ram_consumed = 0;
    while (1)
    {
        ram_consumed += 1;
        malloc(1024);
        printf("%dMio\n", ram_consumed);
    }
    return 69;
}