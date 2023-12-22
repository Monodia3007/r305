#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "minuscule.h"

/**
 * @brief Converts a given string to lowercase.
 *
 * This function takes a null-terminated string as input and returns a new string
 * that is the same as the input string, but with all uppercase characters converted
 * to lowercase. The returned string should be freed by the caller when it is no longer
 * needed.
 *
 * @param chaine The input string to convert to lowercase.
 * @return A new string that is the lowercase version of the input string.
 */
char *minuscule(const char *chaine)
{
    size_t len = strlen(chaine);
    char *result = malloc(len + 1);  // allocate one extra byte for the null-terminator

    for (size_t i = 0; i < len; i++)
    {
        result[i] = tolower(chaine[i]);
    }
    result[len] = '\0';  // null-terminate the result

    return result;
}

/**
 * @brief Runs the "minuscule" function on each input string.
 *
 * This function takes an array of input strings and prints the lowercase version of each string using the "minuscule" function.
 * If the number of arguments is less than 2, an error message is printed and the function returns 1.
 *
 * @param argc The number of input arguments.
 * @param argv An array of input strings.
 * @return 0 if successful, 1 if there is an error.
 */
int run_minuscule(const int argc, const char *argv[])
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