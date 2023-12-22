#include <stdio.h>
#include <unistd.h>
#include <grp.h>
#include <sys/wait.h>
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
    /// echo Bonjour ; sleep 10 ; xeyes & echo Fini
    pid_t const pid_bonjour = fork();

    if (pid_bonjour < 0)
    {
        return 1;
    }
    if (pid_bonjour == 0) 
    {
        execlp("echo", "echo", "Bonjour", NULL);
        perror("execlp");
    }
    waitpid(pid_bonjour, NULL, 0);
    
    pid_t const pid_sleep = fork();

    if (pid_sleep < 0)
    {
        return 1;
    }
    if (pid_sleep == 0) 
    {
        execlp("sleep", "sleep", "10", NULL);
        perror("execlp");
    }
    waitpid(pid_sleep, NULL, 0);
    
    pid_t const pid_xeyes = fork();

    if (pid_xeyes < 0)
    {
        return 1;
    }
    if (pid_xeyes == 0) 
    {
        execlp("xeyes", "xeyes", NULL);
        perror("execlp");
    }
    
    pid_t const pid_fini = fork();

    if (pid_fini < 0)
    {
        return 1;
    }
    if (pid_fini == 0) 
    {
        execlp("echo", "echo", "Fini", NULL);
        perror("execlp");
    }
    return 0;
}