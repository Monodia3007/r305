/**
 * @file archiver.h
 * @brief Header for File Archiving Utility
 *
 * This header file declares the main functions used by the archival utility.
 * These functions facilitate creating an archive of files with '.arch' extension.
 *
 * @author Lilith Camplin
 * @date 2023-10-24
 */

#ifndef R305_ARCHIVER_H
#define R305_ARCHIVER_H

#include <stdint.h>


/**
 * @function int file_size(int fd)
 * @brief Calculates the size of the file represented by the file descriptor.
 *
 * @param fd The file descriptor of the file
 *
 * @return The size of the file in bytes. In the case of an error, returns -1.
 */
int file_size(int fd);

/**
 * @function int copy(int source, int destination)
 * @brief Copies content from the source file to the destination file.
 *
 * @param source The source file descriptor
 * @param destination The destination file descriptor
 *
 * @return The total number of bytes written to the destination file. In the case of error, returns -1.
 */
ssize_t copy(int source, int destination);

/**
 * @function int archive_file(int fd_archive, const char *file)
 * @brief Adds a file to an archive.
 *
 * @param fd_archive The file descriptor of the archive
 * @param file A string pointer to the name of the file to be archived
 *
 * @return The total number of bytes written to the archive, or -1 in the case of errors.
 */
ssize_t archive_file(int fd_archive, const char *file);


/**
 * @function int create_archive(const char *archive_file, char **file_list, uint32_t file_count)
 * @brief Creates an archive and adds multiple files to it.
 *
 * @param archive_file A string pointer to the file name of the archive
 * @param file_list A pointer to the list of file names to be archived
 * @param file_count The number of files in the list
 *
 * @return The total number of bytes written to the archive, including file headers, or -1 in case of errors.
 */
ssize_t create_archive(const char *archive_file, char **file_list, uint32_t file_count);

/**
 * @function int main(int argc, char *argv[])
 * @brief The entry point to the application.
 *
 * Takes command-line arguments for the archive name and the list of files
 * to be archived. The archived file will have the '.arch' extension.
 *
 * @return 0 on successful completion, otherwise it returns 1.
 */
int run_archiver(int argc, char *argv[]);

#endif //R305_ARCHIVER_H
