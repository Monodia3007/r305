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

/**
 * @function int copy(int source, int destination, int size)
 * @brief Copies a certain number of bytes from the source file to the destination file.
 *
 * @param source The source file descriptor
 * @param destination The destination file descriptor
 * @param size The number of bytes to be copied
 *
 * @return The total number of bytes copied, or -1 in case of errors.
 */
int copy(int source, int destination, int size);

/**
 * @function int extract_file(int fd_archive)
 * @brief Extracts a file from an archive.
 *
 * @param fd_archive The file descriptor of the archive
 *
 * @return The total number of bytes written to the extracted file, or -1 in case of errors.
 */
int extract_file(int fd_archive);

/**
 * @function int extract_archive(const char *archive)
 * @brief Extracts all files from an archive.
 *
 * @param archive A string representing the archive filename
 *
 * @return The number of files extracted from the archive, or -1 in case of errors.
 */
int extract_archive(const char *archive);

/**
 * @function int main(int argc, char **argv)
 * @brief The entry point to the application.
 *
 * Takes a command-line argument for the archive file name
 * from which files are to be extracted.
 *
 * @return 0 on successful completion, otherwise it returns 1.
 */
int main(int argc, char **argv);

#endif //R305_UNARCHIVER_H
