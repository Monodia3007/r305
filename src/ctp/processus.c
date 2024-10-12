#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "processus.h"

/**
 * @brief Runs a series of processes in sequence.
 *
 * This function forks multiple child processes and uses `execlp` to execute
 * different commands in each child process. The commands executed are:
 * 1. `echo Bonjour`
 * 2. `sleep 10`
 * 3. `xeyes`
 * 4. `echo Fini`
 * The parent process waits for each child process to complete using `waitpid`.
 *
 * @return 0 on success, 1 on failure
 */
int run_processus(void)
{
    ///echo Bonjour; sleep 10; xeyes & echo Fini
    pid_t pid_bonjour = fork();

    if (pid_bonjour < 0)
    {
        return 1;
    }
    if (pid_bonjour == 0)
    {
        execlp("echo", "echo", "Bonjour", NULL);
        perror("execlp");
        _exit(EXIT_FAILURE);
    }

    if (waitpid(pid_bonjour, NULL, 0) == -1)
    {
        perror("waitpid");
        return 1;
    }

    pid_t pid_sleep = fork();

    if (pid_sleep < 0)
    {
        return 1;
    }
    if (pid_sleep == 0)
    {
        execlp("sleep", "sleep", "10", NULL);
        perror("execlp");
        _exit(EXIT_FAILURE);
    }

    if (waitpid(pid_sleep, NULL, 0) == -1)
    {
        perror("waitpid");
        return 1;
    }

    pid_t pid_xeyes = fork();

    if (pid_xeyes < 0)
    {
        return 1;
    }
    if (pid_xeyes == 0)
    {
        execlp("xeyes", "xeyes", NULL);
        perror("execlp");
        _exit(EXIT_FAILURE);
    }

    pid_t pid_fini = fork();

    if (pid_fini < 0)
    {
        return 1;
    }
    if (pid_fini == 0)
    {
        execlp("echo", "echo", "Fini", NULL);
        perror("execlp");
        _exit(EXIT_FAILURE);
    }

    return 0;
}