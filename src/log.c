#include "log.h"

#include <stdio.h>
#include <stdarg.h>

static FILE* log_fd;

int log_start()
{
    log_fd = fopen("log.txt", "w");
    if (!log_fd)
    {
        fprintf(stderr, "Could not open log file.\n");
        return 1;
    }
    return 0;
}

void log_end()
{
    fclose(log_fd);
    log_fd = 0;
}

void log_info(char const* format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(log_fd, format, args);
    va_end(args);
}

void log_error(char const* format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(log_fd, format, args);
    va_end(args);
}