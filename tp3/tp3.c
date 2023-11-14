#include "tp3.h"
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/syslimits.h>

/**
 * @file
 * @brief This file contains the documentation for the function afficher_infos.
 */
int afficher_infos(const char *chemin) {
    struct stat infos;
    if (stat(chemin, &infos) == -1) {
        perror(chemin);
        return -1;
    }

    char type;
    switch (infos.st_mode & S_IFMT) {
        case S_IFREG: type = '-'; break;
        case S_IFDIR: type = 'd'; break;
        case S_IFLNK: type = 'l'; break;
        default: type = '?'; break;
    }

    printf("%c ", type);
    printf("%o ", infos.st_mode & ~S_IFMT);
    printf("%d ", infos.st_uid);
    printf("%d ", infos.st_gid);
    printf("%lld ", (long long)infos.st_size);
    printf("%s\n", chemin);

    return 0;
}

/**
 * @brief Affiche le contenu d'un répertoire donné.
 *
 * Cette fonction affiche le contenu d'un répertoire donné par le chemin spécifié.
 * Elle affiche uniquement les noms des fichiers et des sous-répertoires présents.
 *
 * @param chemin Le chemin du répertoire à afficher.
 *
 * @return Aucune valeur de retour.
 */
int afficher_repertoire(const char *chemin) {
    DIR *rep = opendir(chemin);
    if (rep == NULL) {
        perror(chemin);
        return -1;
    }

    struct dirent *entree;
    while ((entree = readdir(rep)) != NULL) {
        char chemin_fichier[PATH_MAX];
        snprintf(chemin_fichier, PATH_MAX, "%s/%s", chemin, entree->d_name);

        if (afficher_infos(chemin_fichier) == -1) {
            closedir(rep);
            return -1;
        }
    }

    closedir(rep);
    return 0;
}

/**
 * @file tp3.c
 * @brief Main function for the application.
 *
 * This file contains the main entry point for the application.
 * It parses command line arguments and performs necessary initialization.
 *
 */
int main(int argc, char *argv[]) {
    if (argc == 1) {
        return afficher_repertoire(".");
    }
    for (int i = 1; i < argc; i++) {
        if (afficher_repertoire(argv[i]) == -1) {
            return 1;
        }
    }
    return 0;
}