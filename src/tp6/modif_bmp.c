//
// Created by Lilith Camplin on 19/12/2023.
//

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "modif_bmp.h"

int lire_deux_octets(int fd, uint16_t *val) {
    int result = read(fd, val, sizeof(*val));

    if(result > 0) {
        return sizeof(*val);  // return the number of bytes read
    } else if(result < 0) {
        return -1; // return -1 in case of error
    } else {
        return 0; // return 0 if file is terminated
    }
}

int lire_quatre_octets(int fd, uint32_t *val) {
    int result = read(fd, val, sizeof(*val));

    if(result > 0) {
        return sizeof(*val);  // return the number of bytes read
    } else if(result < 0) {
        return -1; // return -1 in case of error
    } else {
        return 0; // return 0 if file is terminated
    }
}

int lire_entete(int fd, entete_bmp *entete) {
    if(lire_deux_octets(fd, &entete->fichier.signature) != sizeof(entete->fichier.signature)
       || lire_quatre_octets(fd, &entete->fichier.taille_fichier) != sizeof(entete->fichier.taille_fichier)
       || lire_quatre_octets(fd, &entete->fichier.reserve) != sizeof(entete->fichier.reserve)
       || lire_quatre_octets(fd, &entete->fichier.offset_donnees) != sizeof(entete->fichier.offset_donnees)
       || lire_quatre_octets(fd, &entete->bitmap.taille_entete) != sizeof(entete->bitmap.taille_entete)
       || lire_quatre_octets(fd, &entete->bitmap.largeur) != sizeof(entete->bitmap.largeur)
       || lire_quatre_octets(fd, &entete->bitmap.hauteur) != sizeof(entete->bitmap.hauteur)
       || lire_deux_octets(fd, &entete->bitmap.nombre_plans) != sizeof(entete->bitmap.nombre_plans)
       || lire_deux_octets(fd, &entete->bitmap.profondeur) != sizeof(entete->bitmap.profondeur)
       || lire_quatre_octets(fd, &entete->bitmap.compression) != sizeof(entete->bitmap.compression)
       || lire_quatre_octets(fd, &entete->bitmap.taille_donnees_image) != sizeof(entete->bitmap.taille_donnees_image)
       || lire_quatre_octets(fd, &entete->bitmap.resolution_horizontale) != sizeof(entete->bitmap.resolution_horizontale)
       || lire_quatre_octets(fd, &entete->bitmap.resolution_verticale) != sizeof(entete->bitmap.resolution_verticale)
       || lire_quatre_octets(fd, &entete->bitmap.taille_palette) != sizeof(entete->bitmap.taille_palette)
       || lire_quatre_octets(fd, &entete->bitmap.nombre_de_couleurs_importantes) != sizeof(entete->bitmap.nombre_de_couleurs_importantes)) {
        return -1;  // return -1 if any reading operation fails
    }

    return 0;
}

int ecrire_deux_octets(int fd, uint16_t val) {
    ssize_t result = write(fd, &val, sizeof(val));

    if(result != sizeof(val)) {
        return -1;  // return -1 if failed to write
    } else {
        return sizeof(val);  // return the number of bytes written
    }
}

int ecrire_quatre_octets(int fd, uint32_t val) {
    ssize_t result = write(fd, &val, sizeof(val));

    if(result != sizeof(val)) {
        return -1;  // return -1 if failed to write
    } else {
        return sizeof(val);  // return the number of bytes written
    }
}

int ecrire_entete(int fd, entete_bmp *entete) {
    if (ecrire_deux_octets(fd, entete->fichier.signature) == -1
        || ecrire_quatre_octets(fd, entete->fichier.taille_fichier) == -1
        || ecrire_quatre_octets(fd, entete->fichier.reserve) == -1
        || ecrire_quatre_octets(fd, entete->fichier.offset_donnees) == -1
        || ecrire_quatre_octets(fd, entete->bitmap.taille_entete) == -1
        || ecrire_quatre_octets(fd, entete->bitmap.largeur) == -1
        || ecrire_quatre_octets(fd, entete->bitmap.hauteur) == -1
        || ecrire_deux_octets(fd, entete->bitmap.nombre_plans) == -1
        || ecrire_deux_octets(fd, entete->bitmap.profondeur) == -1
        || ecrire_quatre_octets(fd, entete->bitmap.compression) == -1
        || ecrire_quatre_octets(fd, entete->bitmap.taille_donnees_image) == -1
        || ecrire_quatre_octets(fd, entete->bitmap.resolution_horizontale) == -1
        || ecrire_quatre_octets(fd, entete->bitmap.resolution_verticale) == -1
        || ecrire_quatre_octets(fd, entete->bitmap.taille_palette) == -1
        || ecrire_quatre_octets(fd, entete->bitmap.nombre_de_couleurs_importantes) == -1) {

        return -1; // return -1 if any writing operation fails
    }

    return 0;
}

int verifier_entete(const entete_bmp *entete) {
    // verify the image depth is 24 bits
    if(entete->bitmap.profondeur == 24) {
        return 1;   // return 1 if the depth is 24 bits
    } else {
        return 0;   // return 0 otherwise
    }
}

unsigned char* allouer_pixels(entete_bmp *entete) {
    // With BMP pixel data, each pixel requires 3 bytes (24 bits for red, green, and blue)
    unsigned char* pixels = malloc(entete->bitmap.taille_donnees_image * sizeof(unsigned char));
    return pixels;  // return the allocated array
}

int lire_pixels(int fd, entete_bmp *entete, unsigned char *pixels) {
    // move the file cursor to the position where the pixel data begins
    lseek(fd, entete->fichier.offset_donnees, SEEK_SET);

    // read the pixel data into the pixels array
    uint32_t result = read(fd, pixels, entete->bitmap.taille_donnees_image);
    if(result != entete->bitmap.taille_donnees_image) {
        return -1;  // return -1 if failed to read
    }

    return 0;
}

int ecrire_pixels(int fd, entete_bmp *entete, unsigned char *pixels) {
    // move the file cursor to the position where the pixel data begins
    lseek(fd, entete->fichier.offset_donnees, SEEK_SET);

    // write the pixel data from the pixels array
    uint32_t result = write(fd, pixels, entete->bitmap.taille_donnees_image);
    if(result != entete->bitmap.taille_donnees_image) {
        return -1;  // return -1 if failed to write
    }

    return 0;
}

void rouge(entete_bmp *entete, unsigned char *pixels) {
    uint32_t padding = (4 - (entete->bitmap.largeur * 3) % 4) % 4; // line padding calculation
    for (uint32_t line = 0; line < entete->bitmap.hauteur; line++) {
        uint32_t lineoff = line * entete->bitmap.largeur * 3 + line * padding;
        for (uint32_t col = 0; col < entete->bitmap.largeur; col++) {
            uint32_t x = lineoff + col * 3;
            pixels[x] = 0;     // blue
            pixels[x + 1] = 0; // green
            // leaving red channel pixels[x + 2] unmodified
        }
    }
}

void negatif(entete_bmp *entete, unsigned char *pixels) {
    uint32_t padding = (4 - (entete->bitmap.largeur * 3) % 4) % 4; // line padding
    for (uint32_t line = 0; line < entete->bitmap.hauteur; line++) {
        uint32_t lineoff = line * entete->bitmap.largeur * 3 + line * padding;
        for (uint32_t col = 0; col < entete->bitmap.largeur; col++) {
            uint32_t x = lineoff + col * 3;
            pixels[x] = ~pixels[x]; // Invert blue component
            pixels[x + 1] = ~pixels[x + 1]; // Invert green component
            pixels[x + 2] = ~pixels[x + 2]; // Invert red component
        }
    }
}

void noir_et_blanc(entete_bmp *entete, unsigned char *pixels) {
    uint32_t padding = (4 - (entete->bitmap.largeur * 3) % 4) % 4; // line padding
    for (uint32_t line = 0; line < entete->bitmap.hauteur; line++) {
        uint32_t lineoff = line * entete->bitmap.largeur * 3 + line * padding;
        for (uint32_t col = 0; col < entete->bitmap.largeur; col++) {
            uint32_t x = lineoff + col * 3;
            unsigned char average = (pixels[x] + pixels[x + 1] + pixels[x + 2]) / 3;
            pixels[x] = pixels[x + 1] = pixels[x + 2] = average;
        }
    }
}

void moitie(entete_bmp *entete, unsigned char *pixels, int sup) {
    uint32_t padding = (4 - (entete->bitmap.largeur * 3) % 4) % 4; // calculer le padding
    uint32_t bytes_per_row = entete->bitmap.largeur * 3 + padding;
    uint32_t half_height = entete->bitmap.hauteur / 2;
    unsigned char *newPixels;

    // allouer un espace pour la nouvelle image
    newPixels = (unsigned char *)malloc( half_height * bytes_per_row * sizeof(unsigned char) );

    // si sup vaut 1, copier la moitié supérieure de l'image
    if(sup) {
        for(uint32_t i = 0; i < half_height; i++) {
            for(uint32_t j = 0; j < bytes_per_row; j++) {
                newPixels[i * bytes_per_row + j] = pixels[(i + half_height) * bytes_per_row + j];
            }
        }
    } else { // sinon, copier la moitié inférieure de l'image
        for(uint32_t i = 0; i < half_height; i++) {
            for(uint32_t j = 0; j < bytes_per_row; j++) {
                newPixels[i * bytes_per_row + j] = pixels[i * bytes_per_row + j];
            }
        }
    }

    // mettre à jour l'entête pour refléter la nouvelle hauteur
    entete->bitmap.hauteur = half_height;

    // copier les nouveaux pixels dans l'ancien tableau de pixels
    memcpy(pixels, newPixels, half_height * bytes_per_row);
    free(newPixels); // libérer la mémoire allouée pour les nouveaux pixels
}

int run_modif_bmp(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error: Missing input or output file for --modif_bmp operation\n");
        return -1;
    }

    char *input = argv[1];
    char *output = argv[2];

    // Open the input file
    FILE *in = fopen(input, "rb");
    if (!in) {
        printf("Error: Cannot open input file %s\n", input);
        fclose(in);
        return -1;
    }

    // Read the BMP header and the pixel data
    entete_bmp entete;
    if (lire_entete(fileno(in), &entete) == -1) {
        printf("Error: Cannot read BMP header from input file %s\n", input);
        fclose(in);
        return -1;
    }

    // Verify the depth of the BMP file
    if (!verifier_entete(&entete)) {
        printf("Error: Invalid depth in BMP file %s. Expecting 24 bits.\n", input);
        fclose(in);
        return -1;
    }

    unsigned char *pixels = allouer_pixels(&entete);
    if (lire_pixels(fileno(in), &entete, pixels) == -1) {
        printf("Error: Cannot read pixel data from input file %s\n", input);
        free(pixels);
        fclose(in);
        return -1;
    }

    // Close the input file
    fclose(in);

    // Apply filters in the order of arguments
    for (int i = 3; i < argc; i++) {
        if (strcmp(argv[i], "-r") == 0) {
            rouge(&entete, pixels);
        } else if (strcmp(argv[i], "-n") == 0) {
            negatif(&entete, pixels);
        } else if (strcmp(argv[i], "-b") == 0) {
            noir_et_blanc(&entete, pixels);
        } else if (strcmp(argv[i], "-s") == 0) {
            moitie(&entete, pixels, 1);
        } else if (strcmp(argv[i], "-i") == 0) {
            moitie(&entete, pixels, 0);
        }
    }

    // Open the output file
    FILE *out = fopen(output, "wb");
    if (!out) {
        printf("Error: Cannot open output file %s\n", output);
        free(pixels);
        return -1;
    }

    // Write the BMP header and the pixel data
    if (ecrire_entete(fileno(out), &entete) == -1) {
        printf("Error: Cannot write BMP header to output file %s\n", output);
        free(pixels);
        fclose(out);
        return -1;
    }

    if (ecrire_pixels(fileno(out), &entete, pixels) == -1) {
        printf("Error: Cannot write pixel data to output file %s\n", output);
        free(pixels);
        fclose(out);
        return -1;
    }

    // Close the output file and free pixel memory
    fclose(out);
    free(pixels);

    printf("BMP file modified successfully. Output written to %s.\n", output);
    return 0;
}