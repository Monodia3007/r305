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

/**
 * @brief Reads two bytes from a file descriptor into a uint16_t variable.
 *
 * This function reads two bytes from the specified file descriptor and stores them in the provided uint16_t variable. The function returns the number of bytes read, or -1 on error,
* or 0 if the end of the file has been reached.
 *
 * @param fd The file descriptor to read from.
 * @param val A pointer to the uint16_t variable to store the read value into.
 * @return The number of bytes read, or -1 on error, or 0 if end of file.
 */
int lire_deux_octets(int fd, uint16_t *val);

/**
 * @brief Reads four bytes from a file descriptor and stores them in a uint32_t variable.
 *
 * This function reads four bytes from the file specified by the given file descriptor, and stores the result
 * in the memory location pointed to by the val parameter. The file must be opened for reading prior to calling
 * this function. The function returns the number of bytes read, or a specific value to indicate an error or
 * end of file.
 *
 * @param fd The file descriptor of the file to read from.
 * @param val A pointer to a uint32_t variable to store the read value.
 * @return The number of bytes read, or a specific value to indicate an error or end of file.
 *         - The return value is sizeof(*val) when successful.
 *         - The return value is -1 if an error occurred.
 *         - The return value is 0 if the end of file is reached.
 *
 * @see read
 */
int lire_quatre_octets(int fd, uint32_t *val);

/**
 * @brief Read the header from a file descriptor
 *
 * This function reads the header of a BMP file from the given file descriptor.
 * The information is stored in the entete_bmp structure.
 *
 * @param de The file descriptor to read from
 * @param entete Pointer to the entete_bmp structure to store the header information
 * @return 0 if successful, -1 if any reading operation fails
 */
int lire_entete(int de, entete_bmp *entete);

/**
 * @brief Writes the given 16-bit value to the specified file descriptor.
 *
 * This function writes 16 bits of data to the specified file descriptor. It uses the `write`
 * system call to perform the write operation. The function returns the number of bytes
 * successfully written or -1 if an error occurred.
 *
 * @param fd The file descriptor to write to.
 * @param val The 16-bit value to write.
 * @return The number of bytes written or -1 if an error occurred.
 */
int ecrire_deux_octets(int fd, uint16_t val);

/**
 * @brief Writes a 32-bit unsigned integer to a file descriptor.
 *
 * This function writes the provided 32-bit unsigned integer to the specified file descriptor.
 *
 * @param fd The file descriptor to write the data to.
 * @param val The value to be written.
 * @return Returns the number of bytes written if successful, otherwise -1 is returned.
 */
int ecrire_quatre_octets(int fd, uint32_t val);

/**
 * @brief Writes the header of a BMP file to the given file descriptor.
 *
 * This function writes the header information of the BMP file specified
 * by the entete_bmp structure to the file specified by the file descriptor.
 * The header information includes both the file header and the bitmap header.
 *
 * @param vers The version of the BMP file format.
 * @param entete A pointer to the entete_bmp structure containing the header information.
 *
 * @return Returns 0 on success, -1 on failure.
 */
int ecrire_entete(int vers, entete_bmp *entete);

/**
 * @brief Verifies if the header depth of a BMP image is 24 bits.
 *
 * This function takes a pointer to the header of a BMP image and checks if the depth of the image is 24 bits.
 *
 * @param entete Pointer to the entete_bmp structure representing the BMP image header.
 * @return Returns 1 if the depth is 24 bits, otherwise returns 0.
 */
int verifier_entete(const entete_bmp *entete);

/**
 * @brief Allocates memory for pixel data in a BMP image.
 *
 * The function allocates memory for pixel data based on the size of the image.
 * Each pixel requires 3 bytes (24 bits for red, green, and blue).
 * The allocated memory should be freed by the caller when no longer needed.
 *
 * @param entete Pointer to the BMP file header and image header structure.
 * @return Pointer to the allocated memory for pixel data.
 */
unsigned char *allouer_pixels(entete_bmp *entete);

/**
 * @brief Read pixel data from a file.
 *
 * This function reads the pixel data from a file specified by the file descriptor 'fd',
 * as per the provided bitmap header 'entete'. The pixel data is stored in the 'pixels' array.
 *
 * @param fd The file descriptor of the bitmap file.
 * @param entete A pointer to the bitmap header structure.
 * @param pixels A pointer to the array where the pixel data will be stored.
 * @return Returns 0 if the pixel data was successfully read, -1 otherwise.
 */
int lire_pixels(int de, entete_bmp *entete, unsigned char *pixels);

/**
 * Writes the pixel data to a BMP file.
 *
 * @param vers The file descriptor of the BMP file.
 * @param entete A pointer to the BMP header structure.
 * @param pixels An array of pixel data to write.
 *
 * @return 0 if successful, -1 if failed to write.
 */
int ecrire_pixels(int vers, entete_bmp *entete, unsigned char *pixels);

/**
 * @brief Modify the pixels of an image to turn it red.
 *
 * This function takes an entete_bmp structure and an array of pixels.
 * It modifies the pixel values in the array to turn the image red,
 * while leaving the blue and green channels unmodified.
 *
 * @param entete Pointer to the entete_bmp structure containing the image header information.
 * @param pixels Pointer to the array of pixels representing the image.
 */
void rouge(entete_bmp *entete, unsigned char *pixels);

/**
 * @brief Inverts the color of each pixel in the given BMP image data.
 *
 * This function takes an entete_bmp structure containing the BMP image header
 * and an array of image pixels and inverts the color of each pixel by
 * bitwise negation.
 *
 * @param entete A pointer to the entete_bmp structure representing the BMP image header.
 * @param pixels A pointer to the array of image pixels.
 * @return void
 *
 * @note The function modifies the pixel array in place.
 *
 * @see entete_bmp, entete_fichier, entete_bitmap
 */
void negatif(entete_bmp *entete, unsigned char *pixels);

/**
 * @brief Convert an image to black and white.
 *
 * This function takes the header and pixel data of a bitmap image and converts
 * the image to black and white. It calculates the average value of the RGB
 * components of each pixel and sets all three components to that average value.
 *
 * @param entete A pointer to the entete_bmp structure containing the header information of the bitmap image.
 * @param pixels A pointer to the pixel data of the bitmap image.
 */
void noir_et_blanc(entete_bmp *entete, unsigned char *pixels);

/**
 * @brief Splits the given bitmap image into two halves and updates the header accordingly.
 *
 * @param entete Pointer to the header of the bitmap image.
 * @param pixels Pointer to the pixel data of the bitmap image.
 * @param sup Indicator whether to copy the upper half of the image.
 *
 * This function splits the given bitmap image into two halves - either the upper half or the lower half.
 * It calculates the padding required for each row of pixels, allocates memory for the new image,
 * and copies the appropriate half of the image to the new memory space.
 * It then updates the header to reflect the new image height, and finally copies the new pixels back to the original pixel array
 * and frees the memory allocated for the new image.
 *
 * @note The original pixel data (passed to the function) will be modified.
 *
 * Example usage:
 * entete_bmp entete;
 * unsigned char pixels[100];
 * moitie(&entete, pixels, 1);
 */
void moitie(entete_bmp *entete, unsigned char *pixel, int sup);

/**
 * @brief This function modifies a BMP file based on the specified operations.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line arguments.
 * @return int Returns 0 if the BMP file was modified successfully, -1 otherwise.
 */
int run_modif_bmp(int argc, char *argv[]);

#endif //R305_MODIF_BMP_H
