#include <stdio.h>

#include "glfw_callbacks.h"

void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "GLFW error %i: %s\n", error, description);
}

