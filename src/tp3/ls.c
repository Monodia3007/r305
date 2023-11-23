/**
 * @file ls.c
 * @brief File operations, including file system information retrieval and directory listing, with fork support.
 * @author Lilith Camplin
 * @date 14-11-2023
 */

#include "ls.h"
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>
#include <sys/wait.h>

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
 * @brief Prints the octal representation of user, group, and other permissions.
 *
 * This function receives a `mode_t` that represents the file's mode (permissions and type)
 * and prints the user, group, and other permissions in octal format.
 *
 * The permission values for user/group/other are translated to 4 (read), 2 (write),
 * and 1(execute). If a permission is not set, then it is represented by the value 0.
 *
 * @param mode It's a type mode_t variable that holds the file's mode (permissions and type).
 *
 * The function doesn't return a value.
 */
void print_octal_permissions(mode_t const mode)
{
    /* User permissions */
    printf("%o", (mode & S_IRUSR ? 4 : 0) + (mode & S_IWUSR ? 2 : 0) + (mode & S_IXUSR ? 1 : 0));
    /* Group permissions */
    printf("%o", (mode & S_IRGRP ? 4 : 0) + (mode & S_IWGRP ? 2 : 0) + (mode & S_IXGRP ? 1 : 0));
    /* Other permissions */
    printf("%o", (mode & S_IROTH ? 4 : 0) + (mode & S_IWOTH ? 2 : 0) + (mode & S_IXOTH ? 1 : 0));
    putchar(' ');
}

/**
 * @brief This function gets the file or directory information and displays it.
 *
 * The function uses the stat system call to retrieve the file system information.
 * The information includes the type of the file (regular file, directory, or symbolic link),
 * file permissions, user name, group name, file size, and the file path.
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
    if (S_ISREG(infos.st_mode))
    {
        type = '-';
    }
    else if (S_ISDIR(infos.st_mode))
    {
        type = 'd';
    }
    else if (S_ISLNK(infos.st_mode))
    {
        type = 'l';
    }
    else
    {
        type = '?';
    }

    printf("\x001B[1;95m");
    printf("%c ", type);

    // Use custom function to print permissions:
    print_octal_permissions(infos.st_mode);

    struct passwd const *pwd = getpwuid(infos.st_uid);
    struct group const *grp = getgrgid(infos.st_gid);

    if (pwd != NULL)
    {
        printf("%s ", pwd->pw_name);
    } else
    {
        printf("%d ", infos.st_uid);
    }

    if (grp != NULL)
    {
        printf("%s ", grp->gr_name);
    } else
    {
        printf("%d ", infos.st_gid);
    }

    printf("%lld ", infos.st_size);
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
__attribute__((unused)) void traiter(void)
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
    int const pid = fork();

    if (pid == 0)
    { // This is child process
        if (afficher_repertoire(chemin) == -1)
        {
            perror(chemin);
            exit(1);
        }
        exit(0);
    }
    if (pid > 0)
    { // This is parent process
        return pid;
    }
    perror("fork");
    return -1;

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
int run_ls(int const argc, char *argv[])
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