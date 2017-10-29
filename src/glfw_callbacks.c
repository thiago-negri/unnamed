#include <stdio.h>

#include "glfw_callbacks.h"

void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "GLFW error %i: %s\n", error, description);
}

void glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

