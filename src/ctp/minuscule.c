#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char *minuscule(const char *chaine)
{
    char *result = malloc(sizeof(chaine));

    for (int i = 0; i < (int)strlen(chaine); i++)
    {
        result[i] = tolower(chaine[i]);
    }

    return result;
}

int main(const int argc, const char *argv[])
{
    if (argc < 2) 
    {
        fprintf(stderr, "Nombre d'argument invalide\nUsage : %s <string1> [string2] [string3] ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        char *str = minuscule(argv[i]);
        printf("%s\n", str);
        free(str);
    }
    return 0;
}