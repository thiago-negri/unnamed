#include <stdio.h>

#include "glfw_callbacks.h"
#include "window.h"
#include "log.h"

void glfw_callback_error(int error, char const* description)
{
    log_error("GLFW error %i: %s\n", error, description);
}

void glfw_callback_key(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void glfw_callback_size(GLFWwindow* window, int width, int height)
{
    window_data_t* data = glfwGetWindowUserPointer(window);
    data->width = width;
    data->height = height;
    log_info("GLFW size callback: %ix%i\n", width, height);
    glViewport(0, 0, width, height);
}
