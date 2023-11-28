//
// Created by Lilith Camplin on 28/11/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include "shell.h"
#include "ligne_commande.h"

void affiche_prompt()
{
    char hostname[1024], cwd[PATH_MAX];

    // Get user name
    char *user = getenv("USER");
    if (user == NULL)
    {
        printf("Error getting USERNAME.\n");
        return;
    }

    // Get host name
    if (gethostname(hostname, sizeof(hostname)) != 0)
    {
        printf("Error getting HOSTNAME.\n");
        return;
    }

    // Get current working directory
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        printf("Error getting CURRENT WORKING DIRECTORY.\n");
        return;
    }

    // Display the prompt
    printf("%s@%s:%s> ", user, hostname, cwd);
    fflush(stdout); // ensure the prompt gets displayed immediately
}

void execute_ligne_commande(char*** commandes, int const nb, int const arriere_plan)
{
    // loop over all commands
    for (int i = 0; i < nb; i++)
    {
        // taking a command from the 'commandes' array
        char** command = commandes[i];

        // Handle 'cd' command in parent process
        if (strcmp(command[0], "cd") == 0)
        {
            if (command[1] != NULL)
            {
                if(chdir(command[1]) != 0)
                {
                    perror("chdir() error");
                }
            }
            continue;
        }

        // creating a child process to execute the command
        pid_t const pid = fork();

        // error occurred in fork
        if (pid < 0)
        {
            perror("fork() error");
            break;
        }
        if (pid == 0)
        {
            // in child process
            // Execute the command
            if (execvp(command[0], command) < 0)
            {
                perror("execvp() error");
            }
            exit(0);
        }

        // in parent process
        // if the command is supposed to be in the foreground, we will wait
        if (!arriere_plan)
        {
            int status;
            waitpid(pid, &status, 0);

            // check if child process ended normally
            if (WIFEXITED(status) == 0)
            {
                perror("Child process termination error");
            }
        }
    }
}

void run_shell()
{
    printf("\033[35m");
    int flag, nb;

    while (1) {  // Loop forever until we hit a break statement
        affiche_prompt();

        char ***commands = ligne_commande(&flag, &nb);

        // Check if ligne_commande returned NULL (error or no command entered)
        if (commands == NULL) {
            printf("An error occurred while reading commands.\n");
            continue;
        }

        // If the first word of the first command is "exit", exit the shell loop
        if (commands[0][0] && strcmp(commands[0][0], "exit") == 0) {
            libere(commands);  // Free the memory allocated by ligne_commande
            break;
        }

        execute_ligne_commande(commands, nb, flag == 1 ? 1 : 0);

        libere(commands);  // Free the memory allocated by ligne_commande
    }
}
