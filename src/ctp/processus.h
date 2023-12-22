//
// Created by Lilith Camplin on 22/12/2023.
//

#ifndef R305_PROCESSUS_H
#define R305_PROCESSUS_H

/**
 * @brief Runs a series of processes sequentially.
 *
 * This function forks multiple child processes and executes different commands using the `execlp` function.
 * The commands executed are as follows:
 *
 * 1. `echo Bonjour` - Prints "Bonjour" to the stdout.
 * 2. `sleep 10` - Pauses the process execution for 10 seconds.
 * 3. `xeyes` - Opens the xeyes application.
 * 4. `echo Fini` - Prints "Fini" to the stdout.
 *
 * Each command is executed in a separate child process using the `fork` and `execlp` functions.
 * The parent process waits for each child process to complete using the `waitpid` function.
 *
 * @return 0 if all processes executed successfully, otherwise 1.
 */
int run_processus(void);

#endif //R305_PROCESSUS_H
