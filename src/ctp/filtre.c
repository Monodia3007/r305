#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>

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

int afficher_repertoire(const char *chemin, const int taille) 
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

int main(int const argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Nombre d'argument invalide\nUsage : %s <taille> <répertoire>\n", argv[0]);
        return 1;
    }

    afficher_repertoire(argv[2], atoi(argv[1]));

    return 0;
}