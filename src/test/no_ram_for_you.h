#ifndef R305_NO_RAM_FOR_YOU_H
#define R305_NO_RAM_FOR_YOU_H

/**
 * @brief Program to demonstrate infinite memory allocation using malloc
 *
 * This program continuously allocates memory using malloc until it fails.
 * It can be used to test how a system handles memory allocation failures.
 */
void run_infinite_malloc(void);

_Noreturn void run_infinite_fork(void);

#endif //R305_NO_RAM_FOR_YOU_H
