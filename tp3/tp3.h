/**
 * @file tp3.h
 * @brief Header file for TP3 in Project r305.
 *
 * This header file contains the prototypes for the functions used in the tp3.c source file.
 */

#ifndef R305_TP3_H
#define R305_TP3_H

/**
 * @brief Prototype for function to display file or directory information.
 *
 * @param chemin The path of the file or directory.
 * @return Returns 0 if successful; otherwise, it returns -1.
 */
int afficher_infos(const char *chemin);

/**
 * @brief Prototype for function to display the contents of a directory.
 *
 * @param chemin The path of the directory.
 * @return Returns 0 if successful; otherwise, it returns -1.
 */
int afficher_repertoire(const char *chemin);

/**
 * @brief Prototype for function to spawn a child process to execute the `afficher_repertoire` function.
 *
 * @param chemin The path of the directory to list.
 * @return Returns the PID of the child process if successful; otherwise, it returns -1.
 */
int lancer_traitement(const char *chemin);

/**
 * @brief Prototype for the main function.
 *
 * @param argc The number of arguments.
 * @param argv The argument vector.
 * @return Returns 0 if successful; otherwise, it returns 1.
 */
int main(int argc, char *argv[]);

#endif //R305_TP3_H