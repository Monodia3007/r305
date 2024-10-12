//
// Created by Lilith Camplin on 19/12/2023.
//

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "modif_bmp.h"

/**
 * @brief Reads two bytes from a file descriptor and stores them in a uint16_t variable.
 *
 * This function reads two bytes from the file descriptor specified by `fd` and stores the
 * result in the memory pointed by `val`. The file descriptor should be opened in read mode.
 * The number of bytes read is returned.
 *
 * @param[in] fd The file descriptor to read from.
 * @param[out] val A pointer to the variable where the result will be stored.
 *
 * @return The number of bytes read.
 *         - If the return value is greater than 0, it means two bytes were read successfully.
 *         - If the return value is 0, it means the end of file has been reached.
 *         - If the return value is -1, it means an error occurred while reading.
 *
 * @note This function assumes that the memory pointed by `val` has enough space to store two bytes.
 */
int lire_deux_octets(int fd, uint16_t *val)
{
    int result = read(fd, val, sizeof(*val));

    if (result > 0)
    {
        return sizeof(*val);  // return the number of bytes read
    } else if (result < 0)
    {
        return -1; // return -1 in case of error
    } else
    {
        return 0; // return 0 if file is terminated
    }
}

/**
 * @brief Read four bytes from a file descriptor and store them in a uint32_t variable.
 *
 * This function reads four bytes from the file referred to by the file descriptor `fd` and stores them in the variable pointed to by `val`.
 * The number of bytes read is returned as follows:
 *   - If successful, the function returns sizeof(uint32_t) (i.e., 4).
 *   - If an error occurs, the function returns -1.
 *   - If the end of the file is reached, the function returns 0.
 *
 * @param fd The file descriptor of the file to read from.
 * @param val Pointer to the variable where the four bytes will be stored.
 * @return The number of bytes read, -1 if an error occurs, or 0 if the end of the file is reached.
 */
int lire_quatre_octets(int fd, uint32_t *val)
{
    int result = read(fd, val, sizeof(*val));

    if (result > 0)
    {
        return sizeof(*val);  // return the number of bytes read
    } else if (result < 0)
    {
        return -1; // return -1 in case of error
    } else
    {
        return 0; // return 0 if file is terminated
    }
}

/**
 * @brief Reads the header information from a BMP file.
 *
 * This function reads the header information from a BMP file using the provided file descriptor and stores it in the given entete_bmp structure.
 *
 * @param fd The file descriptor of the BMP file.
 * @param entete Pointer to the entete_bmp structure where the header information will be stored.
 * @return 0 if the header information is successfully read, -1 if any reading operation fails.
 */
int lire_entete(int fd, entete_bmp *entete)
{
    if (lire_deux_octets(fd, &entete->fichier.signature) != sizeof(entete->fichier.signature)
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
        ||
        lire_quatre_octets(fd, &entete->bitmap.resolution_horizontale) != sizeof(entete->bitmap.resolution_horizontale)
        || lire_quatre_octets(fd, &entete->bitmap.resolution_verticale) != sizeof(entete->bitmap.resolution_verticale)
        || lire_quatre_octets(fd, &entete->bitmap.taille_palette) != sizeof(entete->bitmap.taille_palette)
        || lire_quatre_octets(fd, &entete->bitmap.nombre_de_couleurs_importantes) !=
           sizeof(entete->bitmap.nombre_de_couleurs_importantes))
    {
        return -1;  // return -1 if any reading operation fails
    }

    return 0;
}

/**
 * @brief Writes a 16-bit value to a file descriptor.
 *
 * This function writes a 16-bit value `val` to the file descriptor `fd`. It uses the `write` system call
 * to write the value as a sequence of 2 bytes.
 *
 * @param fd The file descriptor to write to.
 * @param val The value to write.
 *
 * @return On success, the number of bytes written (`sizeof(val)`). On failure, -1 is returned.
 */
int ecrire_deux_octets(int fd, uint16_t val)
{
    ssize_t result = write(fd, &val, sizeof(val));

    if (result != sizeof(val))
    {
        return -1;  // return -1 if failed to write
    } else
    {
        return sizeof(val);  // return the number of bytes written
    }
}

/**
 * @brief Writes four bytes to a file descriptor.
 *
 * This function writes a 32-bit value to a file descriptor. The value is passed by reference
 * and its bytes are written to the file descriptor in their order of significance (most significant byte first).
 *
 * @param fd The file descriptor to write to.
 * @param val The 32-bit value to write.
 * @return The number of bytes written if successful, -1 if there was an error.
 */
int ecrire_quatre_octets(int fd, uint32_t val)
{
    ssize_t result = write(fd, &val, sizeof(val));

    if (result != sizeof(val))
    {
        return -1;  // return -1 if failed to write
    } else
    {
        return sizeof(val);  // return the number of bytes written
    }
}

/**
 * @brief Writes the contents of the given entete_bmp structure to the specified file descriptor.
 *
 * This function writes the contents of the entete_bmp structure to the specified file descriptor
 * by calling the helper functions ecrire_deux_octets and ecrire_quatre_octets. If any writing operation
 * fails, the function returns -1. Otherwise, it returns 0 to indicate success.
 *
 * @param fd The file descriptor to write to
 * @param entete Pointer to the entete_bmp structure containing the data to be written
 * @return 0 on success, -1 on failure
 */
int ecrire_entete(int fd, entete_bmp *entete)
{
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
        || ecrire_quatre_octets(fd, entete->bitmap.nombre_de_couleurs_importantes) == -1)
    {

        return -1; // return -1 if any writing operation fails
    }

    return 0;
}

/**
 * @brief Verifies if the image depth is 24 bits.
 *
 * This function takes a pointer to an entete_bmp structure as input and
 * checks if the depth of the image, stored in its bitmap field, is equal to
 * 24 bits. If the depth is 24 bits, it returns 1; otherwise, it returns 0.
 *
 * @param entete Pointer to the entete_bmp structure to be verified.
 * @return 1 if the depth is 24 bits, 0 otherwise.
 */
int verifier_entete(const entete_bmp *entete)
{
    // verify the image depth is 24 bits
    if (entete->bitmap.profondeur == 24)
    {
        return 1;   // return 1 if the depth is 24 bits
    } else
    {
        return 0;   // return 0 otherwise
    }
}

/**
 * @brief Allocates memory for storing pixel data.
 *
 * This function allocates a memory block to store pixel data for a BMP image. The size of the memory block is
 * calculated using the size of the image data in the given bitmap header.
 *
 * @param entete The header of the BMP image.
 * @return A pointer to the allocated memory block. Returns NULL if memory allocation failed.
 */
unsigned char *allouer_pixels(entete_bmp *entete)
{
    // With BMP pixel data, each pixel requires 3 bytes (24 bits for red, green, and blue)
    unsigned char *pixels = malloc(entete->bitmap.taille_donnees_image * sizeof(unsigned char));
    return pixels;  // return the allocated array
}

/**
 * @brief Reads the pixel data from a file descriptor into an array.
 *
 * This function moves the file cursor to the position where the pixel data begins,
 * then reads the pixel data into the provided array.
 *
 * @param fd The file descriptor of the file to read from.
 * @param entete A pointer to the entete_bmp structure holding the file headers.
 * @param pixels A pointer to the array where the pixel data will be stored.
 * @return 0 on success, -1 on failure.
 */
int lire_pixels(int fd, entete_bmp *entete, unsigned char *pixels)
{
    // move the file cursor to the position where the pixel data begins
    lseek(fd, entete->fichier.offset_donnees, SEEK_SET);

    // read the pixel data into the pixels array
    uint32_t result = read(fd, pixels, entete->bitmap.taille_donnees_image);
    if (result != entete->bitmap.taille_donnees_image)
    {
        return -1;  // return -1 if failed to read
    }

    return 0;
}

/**
 * @brief Writes pixel data to a file descriptor.
 *
 * This function moves the file cursor to the position where the pixel data begins
 * and writes the pixel data from the pixels array. It returns -1 if failed to write,
 * otherwise it returns 0.
 *
 * @param fd The file descriptor of the file to write the pixel data.
 * @param entete Pointer to the entete_bmp structure containing file and bitmap headers.
 * @param pixels Pointer to the array of pixel data.
 * @return If failed to write, returns -1. Otherwise, returns 0.
 */
int ecrire_pixels(int fd, entete_bmp *entete, unsigned char *pixels)
{
    // move the file cursor to the position where the pixel data begins
    lseek(fd, entete->fichier.offset_donnees, SEEK_SET);

    // write the pixel data from the pixels array
    uint32_t result = write(fd, pixels, entete->bitmap.taille_donnees_image);
    if (result != entete->bitmap.taille_donnees_image)
    {
        return -1;  // return -1 if failed to write
    }

    return 0;
}

/**
* @brief Sets the blue and green channels of the image pixels to 0, leaving the red channel unmodified.
*
* This function modifies the provided image pixels by setting the blue and green color channels of each pixel to 0,
* while leaving the red channel unmodified. The function calculates the line padding based on the image width and
* applies the color modifications for each pixel in the image.
*
* @param entete A pointer to the entete_bmp structure that contains information about the image.
* @param pixels A pointer to the image pixels.
*
* @note The function assumes that the image is in 24-bit RGB format, where pixels are stored consecutively in a 1D array.
* Each pixel is represented by 3 bytes, with the channel order of Blue, Green, and Red.
*/
void rouge(entete_bmp *entete, unsigned char *pixels)
{
    uint32_t padding = (4 - (entete->bitmap.largeur * 3) % 4) % 4; // line padding calculation
    for (uint32_t line = 0; line < entete->bitmap.hauteur; line++)
    {
        uint32_t lineoff = line * entete->bitmap.largeur * 3 + line * padding;
        for (uint32_t col = 0; col < entete->bitmap.largeur; col++)
        {
            uint32_t x = lineoff + col * 3;
            pixels[x] = 0;     // blue
            pixels[x + 1] = 0; // green
            // leaving red channel pixels[x + 2] unmodified
        }
    }
}

/**
 * @brief Inverts the color of each pixel in the given BMP image data.
 *
 * This function takes an entete_bmp structure containing the BMP image header
 * and an array of image pixels and inverts the color of each pixel by
 * bitwise negation.
 *
 * @param entete A pointer to the entete_bmp structure representing the BMP image header.
 * @param pixels A pointer to the array of image pixels.
 */
void negatif(entete_bmp *entete, unsigned char *pixels)
{
    uint32_t padding = (4 - (entete->bitmap.largeur * 3) % 4) % 4; // line padding
    for (uint32_t line = 0; line < entete->bitmap.hauteur; line++)
    {
        uint32_t lineoff = line * entete->bitmap.largeur * 3 + line * padding;
        for (uint32_t col = 0; col < entete->bitmap.largeur; col++)
        {
            uint32_t x = lineoff + col * 3;
            pixels[x] = ~pixels[x]; // Invert blue component
            pixels[x + 1] = ~pixels[x + 1]; // Invert green component
            pixels[x + 2] = ~pixels[x + 2]; // Invert red component
        }
    }
}

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
void noir_et_blanc(entete_bmp *entete, unsigned char *pixels)
{
    uint32_t padding = (4 - (entete->bitmap.largeur * 3) % 4) % 4; // line padding
    for (uint32_t line = 0; line < entete->bitmap.hauteur; line++)
    {
        uint32_t lineoff = line * entete->bitmap.largeur * 3 + line * padding;
        for (uint32_t col = 0; col < entete->bitmap.largeur; col++)
        {
            uint32_t x = lineoff + col * 3;
            unsigned char average = (pixels[x] + pixels[x + 1] + pixels[x + 2]) / 3;
            pixels[x] = pixels[x + 1] = pixels[x + 2] = average;
        }
    }
}

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
 */
void moitie(entete_bmp *entete, unsigned char *pixels, int sup)
{
    uint32_t padding = (4 - (entete->bitmap.largeur * 3) % 4) % 4; // calculer le padding
    uint32_t bytes_per_row = entete->bitmap.largeur * 3 + padding;
    uint32_t half_height = entete->bitmap.hauteur / 2;
    unsigned char *newPixels;

    // allouer un espace pour la nouvelle image
    newPixels = (unsigned char *) malloc(half_height * bytes_per_row * sizeof(unsigned char));

    // si sup vaut 1, copier la moitié supérieure de l'image
    if (sup)
    {
        for (uint32_t i = 0; i < half_height; i++)
        {
            for (uint32_t j = 0; j < bytes_per_row; j++)
            {
                newPixels[i * bytes_per_row + j] = pixels[(i + half_height) * bytes_per_row + j];
            }
        }
    } else
    { // sinon, copier la moitié inférieure de l'image
        for (uint32_t i = 0; i < half_height; i++)
        {
            for (uint32_t j = 0; j < bytes_per_row; j++)
            {
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

/**
 * @brief This function modifies a BMP file based on the specified operations.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line arguments.
 * @return int Returns 0 if the BMP file was modified successfully, -1 otherwise.
 */
int run_modif_bmp(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Error: Missing input or output file for --modif_bmp operation\n");
        return -1;
    }

    char *input = argv[1];
    char *output = argv[2];

    // Open the input file
    FILE *in = fopen(input, "rb");
    if (!in)
    {
        printf("Error: Cannot open input file %s\n", input);
        fclose(in);
        return -1;
    }

    // Read the BMP header and the pixel data
    entete_bmp entete;
    if (lire_entete(fileno(in), &entete) == -1)
    {
        printf("Error: Cannot read BMP header from input file %s\n", input);
        fclose(in);
        return -1;
    }

    // Verify the depth of the BMP file
    if (!verifier_entete(&entete))
    {
        printf("Error: Invalid depth in BMP file %s. Expecting 24 bits.\n", input);
        fclose(in);
        return -1;
    }

    unsigned char *pixels = allouer_pixels(&entete);
    if (lire_pixels(fileno(in), &entete, pixels) == -1)
    {
        printf("Error: Cannot read pixel data from input file %s\n", input);
        free(pixels);
        fclose(in);
        return -1;
    }

    // Close the input file
    fclose(in);

    // Apply filters in the order of arguments
    for (int i = 3; i < argc; i++)
    {
        if (strcmp(argv[i], "-r") == 0)
        {
            rouge(&entete, pixels);
        } else if (strcmp(argv[i], "-n") == 0)
        {
            negatif(&entete, pixels);
        } else if (strcmp(argv[i], "-b") == 0)
        {
            noir_et_blanc(&entete, pixels);
        } else if (strcmp(argv[i], "-s") == 0)
        {
            moitie(&entete, pixels, 1);
        } else if (strcmp(argv[i], "-i") == 0)
        {
            moitie(&entete, pixels, 0);
        }
    }

    // Open the output file
    FILE *out = fopen(output, "wb");
    if (!out)
    {
        printf("Error: Cannot open output file %s\n", output);
        free(pixels);
        return -1;
    }

    // Write the BMP header and the pixel data
    if (ecrire_entete(fileno(out), &entete) == -1)
    {
        printf("Error: Cannot write BMP header to output file %s\n", output);
        free(pixels);
        fclose(out);
        return -1;
    }

    if (ecrire_pixels(fileno(out), &entete, pixels) == -1)
    {
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