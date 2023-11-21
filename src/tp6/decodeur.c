//
// Created by Lilith Camplin on 21/11/2023.
//

#include "decodeur.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

char convertir_inverse(char valeur)
{
    if ('A' <= valeur && valeur <= 'Z') return valeur - 'A';
    if ('a' <= valeur && valeur <= 'z') return valeur - 'a' + 26;
    if ('0' <= valeur && valeur <= '9') return valeur - '0' + 52;
    if (valeur == '+') return 62;
    if (valeur == '/') return 63;
    return -1; // This value will be used for padding ('=') as well
}

void decoder_bloc(const char *source, char *destination, int taille_source)
{
    unsigned char bloc[4];
    for (int i = 0; i < 4; i++) {
        bloc[i] = source[i] == '=' ? 0 : convertir_inverse(source[i]);
    }
    destination[0] = (bloc[0] << 2) | (bloc[1] >> 4);
    if (taille_source > 2) destination[1] = ((bloc[1] & 0x0F) << 4) | (bloc[2] >> 2);
    if (taille_source > 3) destination[2] = ((bloc[2] & 0x03) << 6) | (bloc[3]);
}

int decoder_fichier(int source, int destination)
{
    int lus;
    char buffer_in[4];
    char buffer_out[3];

    while ((lus = read(source, &buffer_in, 4)) > 0) {
        decoder_bloc(buffer_in, buffer_out, lus);
        int toWrite = lus - 1;
        if (buffer_in[lus-1] == '=') --toWrite;
        if (buffer_in[lus-2] == '=') --toWrite;
        if (write(destination, &buffer_out, toWrite) != toWrite) {
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

int run_decodeur(int argc, char *argv[]) {
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

    if (decoder_fichier(sourcefd, destfd) < 0) {
        return 1;
    }

    close(sourcefd);
    close(destfd);

    return 0;
}