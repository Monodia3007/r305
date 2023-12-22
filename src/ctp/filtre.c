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
 * @brief Prints the path of a file if its size is over fileSizeLimit.
 *
 * @return ERR_STAT (-1) if there is a failure in getting the file information.
 *         SUCCESS (0) otherwise.
 */
int printIfOverSize(const char *filePath, const int fileSizeLimit)
{
    struct stat fileInfo;
    if (stat(filePath, &fileInfo) == -1)
    {
        perror(filePath);
        return ERR_STAT;
    }

    if (fileInfo.st_size > fileSizeLimit)
    {
        printf("%s\n", filePath);
    }
    return SUCCESS;
}

/**
 * @brief Display the files in a given directory
 *
 * @return ERR_OPENDIR (-1) if opendir() fails to open the directory.
 *         SUCCESS (0) otherwise.
 */
int checkDirFileSize(const char *dirPath, const int fileSizeLimit)
{
    DIR *dirHandle = opendir(dirPath);
    if (dirHandle == NULL)
    {
        perror(dirPath);
        return ERR_OPENDIR;
    }

    struct dirent *entry;

    while ((entry = readdir(dirHandle)) != NULL)
    {
        char filePath[PATH_MAX];
        snprintf(filePath, PATH_MAX, "%s/%s", dirPath, entry->d_name);

        if (printIfOverSize(filePath, fileSizeLimit) == ERR_STAT)
        {
            closedir(dirHandle);
            return ERR_OPENDIR;
        }
    }

    closedir(dirHandle);
    return SUCCESS;
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

    checkDirFileSize(argv[2], (int)strtol(argv[1], NULL, 10));

    return 0;
}