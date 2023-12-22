//
// Created by Lilith Camplin on 22/12/2023.
//

#ifndef R305_MINUSCULE_H
#define R305_MINUSCULE_H

/**
 * @brief Converts a given string to lowercase.
 *
 * This function takes a string as input and converts all the characters
 * to lowercase. It does not modify the original string but returns a new
 * dynamically allocated string.
 *
 * @param chaine The input string to be converted.
 * @return char* A new string with all characters converted to lowercase.
 *         If the input string is empty or NULL, it returns an empty string.
 *         Memory for the result string is dynamically allocated and should be
 *         freed by the caller using the `free()` function to prevent memory leaks.
 *
 * @note The caller is responsible for freeing the memory of the returned string
 *       to prevent memory leaks.
 *
 * @warning The caller should not free the memory of the input string as it is
 *          not modified by this function.
 */
char *minuscule(const char *chaine);

/**
 * @brief Converts the input strings to lowercase.
 *
 * This function takes an array of strings and converts each string to lowercase
 * using the `minuscule` function. The result is printed to the standard output.
 * The function expects at least one string as an argument.
 *
 * @param argc The number of command-line arguments, including the program name.
 * @param argv An array of strings containing the command-line arguments.
 * @return int The return value of the function (0 on success, non-zero on error).
 *
 * @see minuscule()
 */
int run_minuscule(int argc, const char *argv[]);

#endif //R305_MINUSCULE_H
