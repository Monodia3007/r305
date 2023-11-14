/**
 * @file tp3.c
 * @brief File operations, including file system information retrieval and directory listing, with fork support.
 * @author Lilith Camplin
 * @date 14-11-2023
 */

#include "tp3.h"
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/syslimits.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief This function gets the file or directory information and displays it.
 *
 * The function uses the stat system call to retrieve the file system information.
 * The information includes the type of the file (regular file, directory, or symbolic link),
 * file permissions, user id, group id, file size, and the file path.
 *
 * @param chemin The path of the file or directory.
 * @return Returns 0 if successful; otherwise, it returns -1.
 */
int afficher_infos(const char *chemin)
{
    struct stat infos;
    if (stat(chemin, &infos) == -1)
    {
        perror(chemin);
        return -1;
    }

    char type;
    switch (infos.st_mode & S_IFMT)
    {
        case S_IFREG:
            type = '-';
            break;
        case S_IFDIR:
            type = 'd';
            break;
        case S_IFLNK:
            type = 'l';
            break;
        default:
            type = '?';
            break;
    }

    printf("%c ", type);
    printf("%o ", infos.st_mode & ~S_IFMT);
    printf("%d ", infos.st_uid);
    printf("%d ", infos.st_gid);
    printf("%lld ", (long long) infos.st_size);
    printf("%s\n", chemin);

    return 0;
}

/**
 * @brief This function opens a directory and lists all files and directories in it.
 *
 * The function opens a directory specified by the path, reads all directory entries,
 * and gets and displays information for each entry.
 *
 * @param chemin The path of the directory.
 * @return Returns 0 if successful; otherwise, it returns -1.
 */
int afficher_repertoire(const char *chemin)
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

        if (afficher_infos(chemin_fichier) == -1)
        {
            closedir(rep);
            return -1;
        }
    }

    closedir(rep);
    return 0;
}

/**
 * @brief This function simulates a long running process.
 *
 * The function generates a random sleep time, simulating a long running process.
 * It prints the PID of the process before and after sleeping.
 */
void traiter(void)
{
    srand(getpid());
    printf("Processus de pid %d, je vais faire un traitement très long!\n", getpid());
    sleep(rand() % 10);
    printf("Processus de pid %d, traitement terminé\n", getpid());
}

/**
 * @brief This function starts a child process to list a directory.
 *
 * The function forks a child process to call the function afficher_repertoire.
 *
 * @param chemin The path of the directory to list.
 * @return Returns the PID of the child process if successful; otherwise, it returns -1.
 */
int lancer_traitement(const char *chemin)
{
    int pid = fork();

    if (pid == 0)
    { // This is child process
        if (afficher_repertoire(chemin) == -1)
        {
            perror(chemin);
            exit(1);
        }
        exit(0);
    } else if (pid > 0)
    { // This is parent process
        return pid;
    } else
    { // Fork failed
        perror("fork");
        return -1;
    }
}

/**
 * @brief The main function.
 *
 * The function checks command line arguments for a list of directories.
 * For each directory, it starts a child process to list the directory.
 * It waits for all child processes to finish before exiting.
 *
 * @param argc The number of arguments.
 * @param argv The argument vector.
 * @return Returns 0 if successful; otherwise, it returns 1.
 */
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s dir1 [dir2 ... dirN]\n", argv[0]);
        return 1;
    }

    int *pids = malloc((argc - 1) * sizeof(int));
    for (int i = 1; i < argc; i++)
    {
        pids[i - 1] = lancer_traitement(argv[i]);
        if (pids[i - 1] == -1)
        {
            fprintf(stderr, "Failed to launch process for %s\n", argv[i]);
            free(pids);
            return 1;
        }
    }

    for (int i = 0; i < argc - 1; i++)
    {
        if (waitpid(pids[i], NULL, 0) == -1)
        {
            perror("waitpid");
            free(pids);
            return 1;
        }
    }

    free(pids);
    printf("All child processes finished.\n");
    return 0;
}