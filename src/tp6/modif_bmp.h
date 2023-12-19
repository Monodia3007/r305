//
// Created by Lilith Camplin on 19/12/2023.
//

#ifndef R305_MODIF_BMP_H
#define R305_MODIF_BMP_H

/*
 Pour avoir des types d'une taille connue et fixe,
 on utilise les types définis dans stdint.h
*/
#include <stdint.h>

typedef struct
{
    uint16_t signature;
    uint32_t taille_fichier;
    uint32_t reserve;
    uint32_t offset_donnees;
} entete_fichier;

typedef struct
{
    uint32_t taille_entete;
    uint32_t largeur;
    uint32_t hauteur;
    uint16_t nombre_plans;
    uint16_t profondeur;
    uint32_t compression;
    uint32_t taille_donnees_image;
    uint32_t resolution_horizontale;
    uint32_t resolution_verticale;
    uint32_t taille_palette; /* en nombre de couleurs */
    uint32_t nombre_de_couleurs_importantes; /* 0 */
} entete_bitmap;

typedef struct
{
    entete_fichier fichier;
    entete_bitmap bitmap;
} entete_bmp;

int lire_deux_octets(int fd, uint16_t *val);

int lire_quatre_octets(int fd, uint32_t *val);

int lire_entete(int de, entete_bmp *entete);

int ecrire_deux_octets(int fd, uint16_t val);

int ecrire_quatre_octets(int fd, uint32_t val);

int ecrire_entete(int vers, entete_bmp *entete);

int verifier_entete(const entete_bmp *entete);

unsigned char *allouer_pixels(entete_bmp *entete);

int lire_pixels(int de, entete_bmp *entete, unsigned char *pixels);

int ecrire_pixels(int vers, entete_bmp *entete, unsigned char *pixels);

void rouge(entete_bmp *entete, unsigned char *pixels);

void negatif(entete_bmp *entete, unsigned char *pixels);

void noir_et_blanc(entete_bmp *entete, unsigned char *pixels);

void moitie(entete_bmp *entete, unsigned char *pixel, int sup);

int run_modif_bmp(int argc, char *argv[]);

#endif //R305_MODIF_BMP_H
