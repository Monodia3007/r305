//
// Created by Lilith Camplin on 21/11/2023.
//

#ifndef R305_ENCODER_H
#define R305_ENCODER_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

char convertir(char valeur);
void encoder_bloc(const char *source, int taille_source, char *destination);
int encoder_fichier(int source, int destination);
int run_encodeur(int argc, char *argv[]);

#endif //R305_ENCODER_H
