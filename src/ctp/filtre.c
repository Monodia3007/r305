#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include "filtre.h"

#if defined(__linux__)
#include <linux/limits.h>
#elif defined(__APPLE__)

#include <sys/syslimits.h>

#else
#include <limits.h>
#endif

#ifndef PATH_MAX  // If PATH_MAX is not defined, they define it:
#define PATH_MAX 4096  // This is a common maximum limit
#endif

/**
 * @brief Affiche le chemin d'un fichier si sa taille est supérieure à une taille donnée.
 *
 * @param[in] chemin Le chemin du fichier à vérifier.
 * @param[in] taille La taille maximale autorisée.
 *
 * @return 0 si la taille du fichier est inférieure ou égale à la taille donnée,
 *         -1 en cas d'erreur lors de la récupération des informations du fichier.
 *
 * Cette fonction utilise la fonction stat pour vérifier la taille du fichier
 * spécifié par le chemin donné. Si la taille du fichier est supérieure à la
 * taille donnée, le chemin du fichier est affiché sur la sortie standard.
 */
int afficher_fichier(const char *chemin, const int taille)
{
    struct stat infos;
    if (stat(chemin, &infos) == -1)
    {
        perror(chemin);
        return -1;
    }

    if (infos.st_size > taille)
    {
        printf("%s\n", chemin);
    }
    return 0;
}

/**
 * @brief Display the files in a given directory
 *
 * This function takes a directory path and a maximum file size as input parameters.
 * It opens the directory using the opendir() function and reads each entry using the readdir() function.
 * For each entry, it constructs the full file path by concatenating the directory path and the entry name.
 * Then, it calls the afficher_fichier() function to display the file if its size is greater than the given maximum size.
 * Finally, it closes the directory using the closedir() function and returns 0 if successful, -1 otherwise.
 *
 * @param chemin The path to the directory
 * @param taille The maximum file size
 * @return int 0 if successful, -1 otherwise
 */
int afficher_dossier(const char *chemin, const int taille)
{
    DIR *rep = opendir(chemin);
    if (rep == NULL)
    {
        perror(chemin);
        return -1;
    }

    struct dirent *entree;

    while ((entree = readdir(rep)) != NULL)
    {
        char chemin_fichier[PATH_MAX];
        snprintf(chemin_fichier, PATH_MAX, "%s/%s", chemin, entree->d_name);

        if (afficher_fichier(chemin_fichier, taille) == -1)
        {
            closedir(rep);
            return -1;
        }
    }
    closedir(rep);
    return 0;
}

/**
 * @brief Runs the filtre program.
 *
 * This function is the entry point for the filtre program. It expects two command line arguments: the size and the directory.
 * The size specifies the maximum size for files to be displayed, and the directory specifies the directory to search in.
 *
 * @param argc The number of command line arguments.
 * @param argv The command line arguments values.
 * @return 0 if the program executed successfully, otherwise a non-zero value.
 */
int run_filtre(int const argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Nombre d'argument invalide\nUsage : %s <taille> <répertoire>\n", argv[0]);
        return 1;
    }

    afficher_dossier(argv[2], (int)strtol(argv[1], NULL, 10));

    return 0;
}