#include "loader.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// Load contents of file into memory as a single string, path argument is used just for printing error messages
char *_loader_load_file(const char *path, FILE *file)
{
    int error_number;
    char *file_content;
    long file_size;
    size_t elements_read;

    if (fseek(file, 0L, SEEK_END) != 0)
    {
        error_number = errno;
        fprintf(stderr, "Can not reach end of file '%s'. %i: %s\n", 
                        path, error_number, strerror(error_number));
        return NULL;
    }

    file_size = ftell(file);
    if (file_size < 0L)
    {
        error_number = errno;
        fprintf(stderr, "Can not tell file size '%s'. %i: %s\n",
                        path, error_number, strerror(error_number));
        return NULL;
    }

    if (fseek(file, 0L, SEEK_SET) != 0)
    {
        error_number = errno;
        fprintf(stderr, "Can not reach start of file '%s'. %i: %s\n", 
                        path, error_number, strerror(error_number));
        return NULL;
    }

    file_content = (char *) malloc(sizeof(char) * file_size + 1);
    if (file_content == NULL)
    {
        error_number = errno;
        fprintf(stderr, "Can not allocate memory to read file '%s' with size %li. %i: %s\n", 
                        path, file_size, error_number, strerror(error_number));
        return NULL;
    }

    elements_read = fread(file_content, file_size, 1, file);
    if (elements_read != 1)
    {
        fprintf(stderr, "Elements read from file '%s' is not equals to 1. Elements read: %li, file size: %li.\n",
                        path, elements_read, file_size);
        free(file_content);
        return NULL;
    }

    return file_content;
}

// Load contents of file into memory as single string
char *loader_load_filepath(const char *path)
{
    FILE *file;
    char *file_content;
    int error_number;
    int close_status;

    file = fopen(path, "r");
    if (file == NULL)
    {
        error_number = errno;
        fprintf(stderr, "Can not open file '%s'. %i: %s\n", 
                        path, error_number, strerror(error_number));
        return NULL;
    }

    file_content = _loader_load_file(path, file);

    close_status = fclose(file);
    if (close_status != 0)
    {
        error_number = errno;
        fprintf(stderr, "Can not close file '%s' (ignoring). %i: %s\n",
                        path, error_number, strerror(error_number));
    }

    return file_content;
}

