#include "log.h"

#include <stdio.h>
#include <stdarg.h>

#define LOG_TO_STDOUT

#ifndef LOG_TO_STDOUT
static FILE* log_fd;
#endif

int log_start()
{
#ifndef LOG_TO_STDOUT
    log_fd = fopen("log.txt", "w");
    if (!log_fd)
    {
        fprintf(stderr, "Could not open log file.\n");
        return 1;
    }
#endif
    return 0;
}

void log_end()
{
#ifndef LOG_TO_STDOUT
    fclose(log_fd);
    log_fd = 0;
#endif
}

void log_info(char const* format, ...)
{
    va_list args;
    va_start(args, format);
#ifndef LOG_TO_STDOUT
    vfprintf(log_fd, format, args);
#else
    vfprintf(stdout, format, args);
#endif
    va_end(args);
}

void log_error(char const* format, ...)
{
    va_list args;
    va_start(args, format);
#ifndef LOG_TO_STDOUT
    vfprintf(log_fd, format, args);
#else
    vfprintf(stderr, format, args);
#endif
    va_end(args);
}