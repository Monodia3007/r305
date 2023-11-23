/**
 * @file archiver.c
 * @brief File Archiving Utility
 *
 * This module provides functions to create an archive file (with '.arch' extension).
 * It includes functions to calculate file size, copy contents from one file to another,
 * add a file to an archive and create an archive of multiple files.
 *
 * @author Lilith Camplin
 * @date 2023-10-24
 */

#include <sys/types.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "archiver.h"

/**
 * @function int file_size(int fd)
 * @brief Calculates the size of the file represented by the file descriptor.
 *
 * @param fd The file descriptor of the file
 *
 * @return The size of the file in bytes. In the case of an error, returns -1.
 */
int file_size(int const fd)
{
    off_t const position = lseek(fd, 0, SEEK_CUR);
    off_t const size = lseek(fd, 0, SEEK_END);

    if (size == (off_t) -1)
    {
        return -1;
    }

    if (lseek(fd, position, SEEK_SET) == (off_t) -1)
    {
        return -1;
    }

    return size;
}

/**
 * @function int copy(int source, int destination)
 * @brief Copies content from the source file to the destination file.
 *
 * @param source The source file descriptor
 * @param destination The destination file descriptor
 *
 * @return The total number of bytes written to the destination file. In the case of error, returns -1.
 */
ssize_t copy(int const source, int const destination)
{
    char buffer[1024];
    ssize_t bytes_read;
    ssize_t total = 0;

    while ((bytes_read = read(source, buffer, sizeof(buffer))) > 0)
    {
        ssize_t const bytes_written = write(destination, buffer, bytes_read);
        if (bytes_written == -1)
        {
            return -1;
        }
        total += bytes_written;
    }

    if (bytes_read == -1)
    {
        return -1;
    }

    return total;
}

/**
 * @function int archive_file(int fd_archive, const char *file)
 * @brief Adds a file to an archive.
 *
 * @param fd_archive The file descriptor of the archive
 * @param file A string pointer to the name of the file to be archived
 *
 * @return The total number of bytes written to the archive, or -1 in the case of errors.
 */
ssize_t archive_file(int const fd_archive, const char *file)
{
    int const fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        return -1;
    }

    int const size = file_size(fd);
    if (size == -1)
    {
        close(fd);
        return -1;
    }

    uint8_t const file_name_size = strlen(file);
    uint64_t const compressed_size = size;

    write(fd_archive, &file_name_size, sizeof(file_name_size));
    write(fd_archive, file, file_name_size);
    write(fd_archive, &compressed_size, sizeof(compressed_size));

    ssize_t const written = copy(fd, fd_archive);

    close(fd);

    if (written == -1) return -1;
    return written + (ssize_t) sizeof(file_name_size) + (ssize_t) file_name_size +(ssize_t) sizeof(compressed_size);
}


/**
 * @function int create_archive(const char *archive_f, char **file_list, uint32_t file_count)
 * @brief Creates an archive and adds multiple files to it.
 *
 * @param archive_f A string pointer to the file name of the archive
 * @param file_list A pointer to the list of file names to be archived
 * @param file_count The number of files in the list
 *
 * @return The total number of bytes written to the archive, including file headers, or -1 in case of errors.
 */
ssize_t create_archive(const char *archive_f, char **file_list, uint32_t file_count)
{
    int const fd = open(archive_f, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        return -1;
    }

    uint32_t const file_count_le = __builtin_bswap32(file_count);
    write(fd, &file_count_le, sizeof(file_count));

    ssize_t total = sizeof(file_count);
    for (uint32_t i = 0; i < file_count; i++)
    {
        ssize_t const written = archive_file(fd, file_list[i]);
        if (written == -1)
        {
            close(fd);
            return -1;
        }
        total += written;
    }

    close(fd);
    return total;
}

/**
 * @function int main(int argc, char *argv[])
 * @brief The entry point to the application.
 *
 * Takes command-line arguments for the archive name and the list of files
 * to be archived. The archived file will have the '.arch' extension.
 *
 * @return 0 on successful completion, otherwise it returns 1.
 */
int run_archiver(int const argc, char *argv[])
{

    if (argc < 3)
    {
        fprintf(stderr, "Usage : %s <archive_filename> <file1> [file2] ...\n", argv[0]);
        return 1;
    }

    char archive_f[255];
    strncpy(archive_f, argv[1], sizeof(archive_f) - 1);
    archive_f[sizeof(archive_f) - 1] = '\0';  // ensure null termination

    // Append .arch extension if it's not present
    size_t const len = strlen(archive_f);
    if (len <= 5 || strcmp(archive_f + len - 5, ".arch") != 0)
    {
        strncat(archive_f, ".arch", sizeof(archive_f) - len - 1);
    }

    char **file_list = &argv[2];
    uint32_t const file_count = argc - 2;

    ssize_t const result = create_archive(archive_f, file_list, file_count);

    if (result == -1)
    {
        perror("An error occurred while creating the archive.");
        return 1;
    }

    printf("The archive '%s' has been successfully created. Size : %zd bytes\n", archive_f, result);
    return 0;
}