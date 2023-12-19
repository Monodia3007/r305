//
// Created by Lilith Camplin on 21/11/2023.
//

#include "encoder.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * @brief Converts a character value to an integer.
 *
 * This function takes a character value, 'valeur', interprets it as an unsigned integer, and manipulates it
 * to return a character based on the ASCII value of the integer.
 *
 * @param valeur The character value to be converted.
 * @return The integer value representation of the character.
 */
char convertir(char const valeur)
{
    if (valeur >= 0 && valeur < 26) return 'A' + valeur;
    if (valeur >= 26 && valeur < 52) return 'a' + (valeur - 26);
    if (valeur >= 52 && valeur < 62) return '0' + (valeur - 52);
    if (valeur == 62) return '+';
    if (valeur == 63) return '/';
    return -1;
}

/**
 * @brief Encodes a block from the source file.
 *
 * This function takes a block of characters from the source file and encodes it
 * using the convertir function and a specific encoding algorithm.
 *
 * @param source A pointer to the block to be encoded.
 * @param taille_source The size of the block to be encoded.
 * @param destination A pointer to where the encoded block will be stored.
 */
void encoder_bloc(const char *source, int const taille_source, char *destination)
{
    char bloc[4];
    bloc[0] = convertir(source[0] >> 2);
    bloc[1] = convertir((source[0] & 3) << 4 | (source[1] & 0xF0) >> 4);
    bloc[2] = taille_source > 1 ? convertir((source[1] & 0xF) << 2 | source[2] >> 6) : '=';
    bloc[3] = taille_source > 2 ? convertir(source[2] & 0x3F) : '=';

    for(int i = 0; i < 4; i++) {
        destination[i] = bloc[i];
    }
}

/**
 * @brief Encodes a file using a specific algorithm and saves the encoded file to a destination file.
 *
 * This function takes the source file and encodes it consecutively using the encoder_bloc function
 * The encoded file is then saved to the destination file.
 *
 * @param source The file descriptor of the source file to encode.
 * @param destination The file descriptor of the destination file to save the encoded data.
 * @return Returns 0 on successful encoding, and -1 on error.
 */
int encoder_fichier(int const source, int const destination)
{
    int lus;
    char buffer_in[3];
    char buffer_out[4];

    while ((lus = read(source, &buffer_in, 3)) > 0) {
        encoder_bloc(buffer_in, lus, buffer_out);
        if (write(destination, &buffer_out, 4) != 4) {
            perror("Erreur lors de l'ecriture");
            return -1;
        }
    }
    if (lus < 0) {
        perror("Erreur lors de la lecture");
        return -1;
    }
    return 0;
}

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
int run_encodeur(int const argc, char *argv[]) {
    int sourcefd = 0;  // stdin
    int destfd = 1;   // stdout

    if (argc > 1) {
        sourcefd = open(argv[1], O_RDONLY);
        if (sourcefd < 0) {
            perror("Erreur lors de l'ouverture du fichier source");
            return 1;
        }
    }

    if (argc > 2) {
        destfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (destfd < 0) {
            perror("Erreur lors de l'ouverture du fichier destination");
            return 1;
        }
    }

    if (encoder_fichier(sourcefd, destfd) < 0) {
        return 1;
    }

    close(sourcefd);
    close(destfd);

    return 0;
}