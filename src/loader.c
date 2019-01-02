#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "loader.h"

// Load contents of file into memory as a single string, path argument is used just for printing error messages
char* _loader_load_file(char const* path, FILE* file)
{
    if (fseek(file, 0L, SEEK_END))
    {
        errno_t error_number = errno;
        char error_str[100];
        strerror_s(error_str, 99, error_number);
        fprintf(stderr, "Can not reach end of file '%s'. %i: %s\n", 
                        path, error_number, error_str);
        return 0;
    }

    long file_size = ftell(file);
    if (file_size < 0L)
    {
        errno_t error_number = errno;
        char error_str[100];
        strerror_s(error_str, 99, error_number);
        fprintf(stderr, "Can not tell file size '%s'. %i: %s\n",
                        path, error_number, error_str);
        return 0;
    }

    if (fseek(file, 0L, SEEK_SET))
    {
        errno_t error_number = errno;
        char error_str[100];
        strerror_s(error_str, 99, error_number);
        fprintf(stderr, "Can not reach start of file '%s'. %i: %s\n", 
                        path, error_number, error_str);
        return 0;
    }

    char* file_content = calloc(file_size + 1, sizeof(char));
    if (!file_content)
    {
        errno_t error_number = errno;
        char error_str[100];
        strerror_s(error_str, 99, error_number);
        fprintf(stderr, "Can not allocate memory to read file '%s' with size %li. %i: %s\n", 
                        path, file_size, error_number, error_str);
        return 0;
    }

    size_t elements_read = fread(file_content, 1, file_size, file);
    if (elements_read != file_size)
    {
        fprintf(stderr, "Elements read from file '%s' is not equals to file size. Elements read: %li, file size: %li.\n",
                        path, elements_read, file_size);
        free(file_content);
        return 0;
    }

    // Make sure string is 0 terminated.
    file_content[elements_read] = 0;

    return file_content;
}

// Load contents of file into memory as single string
char* loader_load_filepath(char const* path)
{
    FILE* file;
    errno_t fopen_error_number = fopen_s(&file, path, "rb");
    if (fopen_error_number)
    {
        char error_str[100];
        strerror_s(error_str, 99, fopen_error_number);
        fprintf(stderr, "Can not open file '%s'. %i: %s\n", 
                        path, fopen_error_number, error_str);
        return 0;
    }

    char* file_content = _loader_load_file(path, file);

    if (fclose(file))
    {
        errno_t error_number = errno;
        char error_str[100];
        strerror_s(error_str, 99, error_number);
        fprintf(stderr, "Can not close file '%s' (ignoring). %i: %s\n",
                        path, error_number, error_str);
    }

    return file_content;
}

