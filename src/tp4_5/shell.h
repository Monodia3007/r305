//
// Created by Lilith Camplin on 28/11/2023.
//

#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>

/**
 * @function display_prompt
 * Displays a command-line prompt to the user.
 */
void display_prompt();

/**
 * @function replace_home_with_tilde
 * Replaces home directory with '~' in the provided path string.
 *
 * @param currentDirectory The current directory string to manipulate.
 */
void replace_home_with_tilde(char *currentDirectory);

/**
 * @function execute_command_line
 * Executes each command in a given array of commands.
 * If the background flag is set, the commands are run in the background.
 *
 * @param commands 3D array containing each command to execute.
 * @param commandCount Array size (i.e., number of commands).
 * @param backgroundFlag 1 if commands are to be run in background, 0 otherwise.
 */
void execute_command_line(char ***commands, int commandCount, int backgroundFlag);

/**
 * @function launch_command
 * Launches a given command by creating a new process.
 *
 * @param in File descriptor for standard input.
 * @param out File descriptor for standard output.
 * @param command String containing the command to be executed.
 * @param argv Array of arguments for the command.
 * @return The process ID of the newly created process.
 */
int launch_command(int in, int out, const char *command, char **argv);

/**
 * @function run_shell
 * Starts the shell program, executing until an "exit" command is entered.
 * This is the main function from which all other shell functionalities are triggered.
 */
void run_shell();

#endif //SHELL_H
