/**
 * @file decodeur.h
 * @brief Header file for the decoder program.
 *
 * Contains declarations for functions converting decimal digits into their ASCII
 * representation, decoding a block of characters, decoding an entire file and running the decoder program.
 *
 * @date 21/11/2023
 * @author Lilith Abigail Camplin
 */

#ifndef R305_DECODEUR_H
#define R305_DECODEUR_H

char convertir_inverse(char valeur); ///< Performs inverse conversion of a char value to a numeric value.
void decoder_bloc(const char *source, char *destination, int taille_source); ///< Decodes a block of characters from the source file.
int decoder_fichier(int source, int destination); ///< Decodes an entire file and writes the decoded content to the destination file.
int run_decodeur(int argc, char *argv[]); ///< Executing the decoder program.

#endif //R305_DECODEUR_H
