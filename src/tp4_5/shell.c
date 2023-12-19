//
// Created by Lilith Camplin on 28/11/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <pwd.h>
#include "shell.h"
#include "ligne_commande.h"

#if defined(__linux__)
#include <linux/limits.h>
#elif defined(__APPLE__)
#include <sys/syslimits.h>
#else
    #include <limits.h>
#endif

/**
 * Display the shell prompt with username, hostname and current directory.
 */
void display_prompt()
{
    char hostname[1024], cwd[PATH_MAX];

    // Get username
    char* username = getenv("USER");
    if (username == NULL)
    {
        printf("Error getting USERNAME.\n");
        return;
    }

    // Get hostname
    if (gethostname(hostname, sizeof(hostname)) != 0)
    {
        printf("Error getting HOSTNAME.\n");
        return;
    }

    // Remove '.local' from hostname
    char* hostExtension = strstr(hostname, ".local");
    if (hostExtension) *hostExtension = '\0';

    // Get current working directory
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        printf("Error getting CURRENT WORKING DIRECTORY.\n");
        return;
    }

    // Replace home directory with '~'
    replace_home_with_tilde(cwd);

    // Display the prompt
    printf("\033[35m");
    printf("%s@%s:%s> ", username, hostname, cwd);
    fflush(stdout); // ensure the prompt gets displayed immediately
}

/**
 * Replaces the home directory path with '~'
 * @param currentDirectory The current directory string
 */
void replace_home_with_tilde(char* currentDirectory)
{
    // Get user home directory
    struct passwd const* pw = getpwuid(getuid());
    const char* homeDirectory = pw->pw_dir;


    // Convert absolute path to home-relative path
    if (strncmp(currentDirectory, homeDirectory, strlen(homeDirectory)) == 0)
    // if current directory starts with home directory
    {
        char tempDirectory[PATH_MAX];
        sprintf(tempDirectory, "~%s", &currentDirectory[strlen(homeDirectory)]);
        strcpy(currentDirectory, tempDirectory);
    }
}

/**
 * Executes provided command line
 * @param commands The command to execute
 * @param commandCount The number of command
 * @param backgroundFlag Flag to execute in background
 */
void execute_command_line(char*** const commands, int const commandCount, int const backgroundFlag)
{
    int in = 0;
    int out;

    for (int i = 0; i < commandCount; i++)
    {
        // Gérer la commande 'cd' dans le processus parent
        if (strcmp(commands[i][0], "cd") == 0)
        {
            if (commands[i][1] != NULL)
            {
                if (chdir(commands[i][1]) != 0)
                {
                    perror("chdir() error");
                }
            }
            else
            {
                chdir(getenv("HOME")); // aller au répertoire d'accueil
            }
            continue;
        }

        int p[2];
        pipe(p);

        if (i == commandCount - 1)
        {
            out = 1;
        }
        else
        {
            out = p[1];
        }

        pid_t const pid = launch_command(in, out, commands[i][0], commands[i]);

        if (in != 0) close(in);
        if (out != 1) close(out);

        in = p[0];

        if (!backgroundFlag)
        {
            // attendre la fin de l'exécution de la commande si elle n'est pas exécutée en arrière-plan
            int status;
            waitpid(pid, &status, 0);
        }
    }
}

/**
 * Creates a new process and executes a command.
 * @param in File descriptor for stdin
 * @param out File descriptor for stdout
 * @param command The command to be executed
 * @param argv The arguments for the command
 * @return Process ID of created process
 */
int launch_command(int const in, int const out, const char* command, char** argv)
{
    pid_t const pid = fork(); // on crée un nouveau processus par clonage du processus courant

    if (pid < 0)
    {
        // le fork a échoué
        return -1;
    }
    if (pid == 0)
    {
        // ici on se trouve dans le processus fils
        if (in != 0)
        {
            // vérifier s'il faut rediriger l'entrée standard
            dup2(in, 0); // remplace l'entrée standard (0) par le descripteur de fichier "in"
            close(in); // fermer le descripteur de fichier "in" car on n'en a plus besoin
        }

        if (out != 1)
        {
            // vérifier s'il faut rediriger la sortie standard
            dup2(out, 1); // remplace la sortie standard (1) par le descripteur de fichier "out"
            close(out); // fermer le descripteur de fichier "out" car on n'en a plus besoin
        }

        execvp(command, argv); // exécute la commande "com" avec le tableau d'arguments "argv"
        perror("execvp"); // s'exécute seulement si execvp échoue
        _exit(1);
    }

    return pid; // retourne le PID du processus créé
}

/**
 * Main run function for the shell command
 */
void run_shell()
{
    int flag, nb;

    while (1)
    {
        // Loop forever until we hit a break statement
        display_prompt();

        char*** commands = ligne_commande(&flag, &nb);

        // Check if ligne_commande returned NULL (error or no command entered)
        if (commands == NULL)
        {
            printf("An error occurred while reading commands.\n");
            continue;
        }

        // If the first word of the first command is "exit", exit the shell loop
        if (commands[0][0] && strcmp(commands[0][0], "exit") == 0)
        {
            libere(commands); // Free the memory allocated by ligne_commande
            break;
        }

        execute_command_line(commands, nb, flag == 1 ? 1 : 0);

        libere(commands); // Free the memory allocated by ligne_commande
    }
}
