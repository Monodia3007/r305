/**
 * @file unarchiver.h
 * @brief Header for File Extraction Utility
 *
 * This header file declares the main functions used by the extraction utility.
 * These functions facilitate extracting files from an archive with '.arch' extension.
 *
 * @author Lilith Camplin
 * @date 2023-10-24
 */

#ifndef R305_UNARCHIVER_H
#define R305_UNARCHIVER_H

#include <stdint.h>


/**
 * @brief Copy content from a source file descriptor to a destination file descriptor.
 *
 * This function copies the content from one file descriptor to another. It reads data from the source file descriptor,
 * and writes that data to the destination file descriptor. The size parameter determines the number of bytes to be
 * copied. If the size is negative, all data from the source file descriptor until EOF is copied.
 *
 * @param source The source file descriptor to read data from.
 * @param destination The destination file descriptor to write data to.
 * @param size The number of bytes to be copied. Negative value means copying until EOF.
 *
 * @return On success, the total number of bytes copied is returned. On error, -1 is returned, and an error message is
 * displayed.
 *
 * @note The source and destination file descriptors must be opened for reading and writing respectively before being
 * passed to this function.
 */
ssize_t copy_content(int source, int destination, ssize_t size);

/**
 * @function int extract_file(int fd_archive)
 * @brief Extracts a file from an archive.
 *
 * @param fd_archive The file descriptor of the archive
 *
 * @return The total number of bytes written to the extracted file, or -1 in case of errors.
 */
ssize_t extract_file(int fd_archive);

/**
 * @function int extract_archive(const char *archive)
 * @brief Extracts all files from an archive.
 *
 * @param archive A string representing the archive filename
 *
 * @return The number of files extracted from the archive, or -1 in case of errors.
 */
uint32_t extract_archive(const char *archive);

/**
 * @function int main(int argc, char **argv)
 * @brief The entry point to the application.
 *
 * Takes a command-line argument for the archive file name
 * from which files are to be extracted.
 *
 * @return 0 on successful completion, otherwise it returns 1.
 */
int run_unarchiver(int argc, char **argv);

#endif //R305_UNARCHIVER_H
