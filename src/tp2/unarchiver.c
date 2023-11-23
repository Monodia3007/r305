/**
 * @file unarchiver.c
 * @brief File Extraction Utility
 *
 * This file contains functions for extracting files from an existing '.arch' file (archive).
 * It includes functions to copy content from the archive file to a new file,
 * extract a single file from an archive, and extract all files from an archive.
 *
 * @author Lilith Camplin
 * @date 2023-10-24
 */

#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include "unarchiver.h"

/**
 * @function int copy_content(int source, int destination, int size)
 * @brief Copies a certain number of bytes from the source file to the destination file.
 *
 * @param source The source file descriptor
 * @param destination The destination file descriptor
 * @param size The number of bytes to be copied
 *
 * @return The total number of bytes copied, or -1 in case of errors.
 */
ssize_t copy_content(int const source, int const destination, ssize_t size)
{
    ssize_t total = 0;
    while (size > 0)
    {
        char buffer[1024];
        ssize_t const bytes_to_read = (int) sizeof(buffer) < size ? (int) sizeof(buffer) : size;
        ssize_t const read_bytes = read(source, buffer, bytes_to_read);
        if (read_bytes < 0)
        {
            perror("Read error in copy_content");
            return -1;
        }
        if (read_bytes == 0)
        {
            fprintf(stderr, "EOF encountered in copy_content with %zd bytes left to read\n", size);
            return -1;
        }

        ssize_t written_bytes = 0;
        while (written_bytes < read_bytes)
        {
            ssize_t const result = write(destination, buffer + written_bytes, read_bytes - written_bytes);
            if (result < 0)
            {
                perror("Write error in copy_content");
                return -1;
            }
            written_bytes += result;
        }
        total += written_bytes;
        size -= written_bytes;
    }
    return total;
}

/**
 * @function int extract_file(int fd_archive)
 * @brief Extracts a file from an archive.
 *
 * @param fd_archive The file descriptor of the archive
 *
 * @return The total number of bytes written to the extracted file, or -1 in case of errors.
 */
ssize_t extract_file(int const fd_archive)
{
    uint8_t file_name_size;
    if (read(fd_archive, &file_name_size, sizeof(file_name_size)) != sizeof(file_name_size))
    {
        perror("Error reading file name size");
        return -1;
    }

    char file_name[file_name_size + 1];
    if (read(fd_archive, file_name, file_name_size) != file_name_size)
    {
        perror("Error reading file name");
        return -1;
    }
    file_name[file_name_size] = '\0';

    uint64_t file_size;
    if (read(fd_archive, &file_size, sizeof(file_size)) != sizeof(file_size))
    {
        perror("Error reading file size");
        return -1;
    }

    int const fd_file = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd_file == -1)
    {
        perror("Error opening file for writing");
        return -1;
    }

    ssize_t const res = copy_content(fd_archive, fd_file, file_size);

    close(fd_file);

    return res;
}

/**
 * @function int extract_archive(const char *archive)
 * @brief Extracts all files from an archive.
 *
 * @param archive A string representing the archive filename
 *
 * @return The number of files extracted from the archive, or -1 in case of errors.
 */
uint32_t extract_archive(const char *archive)
{
    int const fd = open(archive, O_RDONLY);
    if (fd == -1)
    {
        return -1;
    }

    uint32_t file_count;
    if (read(fd, &file_count, sizeof(file_count)) != sizeof(file_count))
    {
        close(fd);
        return -1;
    }

    for (uint32_t i = 0; i < file_count; i++)
    {
        if (extract_file(fd) == -1)
        {
            close(fd);
            return -1;
        }
    }

    close(fd);

    return file_count;
}

/**
 * @function int main(int argc, char **argv)
 * @brief The entry point to the application.
 *
 * Takes a command-line argument for the archive file name
 * from which files are to be extracted.
 *
 * @return 0 on successful completion, otherwise it returns 1.
 */
int run_unarchiver(int const argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s [archive file]\n", argv[0]);
        return 1;
    }

    uint32_t const result = extract_archive(argv[1]);
    if (result == -1u)
    {
        perror("Error extracting archive");
        return 1;
    }

    printf("Successfully extracted %d file(s) from the archive.\n", result);


    return 0;
}