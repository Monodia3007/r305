//
// Created by Lilith Camplin on 21/11/2023.
//

#ifndef R305_ENCODER_H
#define R305_ENCODER_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * @brief Converts a character value to an integer.
 *
 * This function takes a character value, 'valeur', interprets it as an unsigned integer,
 * and manipulates it to return a character based on the ASCII value of the integer.
 *
 * @param valeur The character value to be converted.
 * @return The integer value representation of the character. If the input character is not within the range
 *         [0, 63], -1 is returned.
 */
char convertir(char valeur);

/**
 * @brief Encodes a block from the source file using a specific encoding algorithm.
 *
 * This function takes a block of characters from the source file and encodes it using
 * the convertir function and a specific encoding algorithm. The encoded block is stored
 * in the destination array.
 *
 * @param source A pointer to the block of characters to be encoded.
 * @param taille_source The size of the block to be encoded.
 * @param destination A pointer to the array where the encoded block will be stored.
 */
void encoder_bloc(const char *source, int taille_source, char *destination);

/**
 * @brief Encodes a file using a specific algorithm and saves the encoded file to a destination file.
 *
 * This function takes the source file and encodes it consecutively using the encoder_bloc function.
 * The encoded file is then saved to the destination file.
 *
 * @param source The file descriptor of the source file to encode.
 * @param destination The file descriptor of the destination file to save the encoded data.
 * @return Returns 0 on successful encoding, and -1 on error.
 */
int encoder_fichier(int source, int destination);

/**
 * @brief Runs the encoder program.
 *
 * This function runs the encoder program. It opens and encodes a source file, then writes the encoded data
 * to a destination file.
 *
 * @param argc The argument count.
 * @param argv An array of arguments.
 * @return Returns 0 on successful execution, and 1 on error.
 */
int run_encodeur(int argc, char *argv[]);

#endif //R305_ENCODER_H
