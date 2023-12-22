#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>
#include <sys/wait.h>
#include <inttypes.h>

int main(void)
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