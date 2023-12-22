//
// Created by Lilith Camplin on 22/12/2023.
//

#ifndef R305_FILTRE_H
#define R305_FILTRE_H

typedef enum
{
    SUCCESS = 0,
    ERR_STAT = -1,
    ERR_OPENDIR = -1,
    ERR_ARGC = 1,
} Status;

/**
 * @brief Afficher le nom d'un fichier si sa taille est supérieure à une valeur donnée.
 *
 * @param chemin Le chemin du fichier à afficher.
 * @param taille La taille minimale du fichier pour être affiché.
 * @return 0 si le fichier a été affiché avec succès, -1 sinon.
 */
int printIfOverSize(const char *filePath, int fileSizeLimit);

/**
 * @brief Displays the files in a directory that have a size greater than a specified value.
 *
 * This function displays the names of the files in the given directory that have a size greater than the specified value.
 *
 * @param chemin The path of the directory to be displayed.
 * @param taille The minimum size of the files to be displayed.
 * @return 0 on success, -1 on error.
 */
int checkDirFileSize(const char *dirPath, int fileSizeLimit);

/**
 * @brief Runs the filtre program with the given command-line arguments.
 *
 * This function expects two command-line arguments: the size and the directory path.
 * It will print an error message and return 1 if the number of arguments is invalid.
 * Otherwise, it calls the afficher_dossier function to process the directory.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of strings containing the command-line arguments.
 * @return 0 if the program executed successfully, 1 if the number of arguments is invalid.
 */
int run_filtre(int argc, char *argv[]);

#endif //R305_FILTRE_H
