//
// Created by Lilith Camplin on 21/11/2023.
//

#ifndef R305_DECODEUR_H
#define R305_DECODEUR_H

char convertir_inverse(char valeur);
void decoder_bloc(const char *source, char *destination, int taille_source);
int decoder_fichier(int source, int destination);
int run_decodeur(int argc, char *argv[]);

#endif //R305_DECODEUR_H
