#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window.h"
#include "log.h"
#include "glfw_callbacks.h"

window_data_t* window_start(char const* title, int width, int height)
{
    glfwSetErrorCallback(glfw_callback_error);

    if (glfwInit() != GLFW_TRUE)
    {
        log_error("Could not initialize GLFW.\n");
        return 0;
    }

    int glfw_major, glfw_minor, glfw_revision;
    glfwGetVersion(&glfw_major, &glfw_minor, &glfw_revision);
    log_info("GLFW %i.%i.%i (compiled with %i.%i.%i)\n",
        glfw_major, glfw_minor, glfw_revision,
        GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);

    GLFWwindow* window = glfwCreateWindow(width, height, title, 0, 0);
    if (!window)
    {
        log_error("Could not open window.\n");
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(window);

    GLenum glew_init_result = glewInit();
    if (glew_init_result)
    {
        log_error("Could not initialize GLEW.\n");
        glfwTerminate();
        return 0;
    }

    GLubyte const* gl_version = glGetString(GL_VERSION);
    log_info("OpenGL %s\n", gl_version);

    glfwSwapInterval(1);

    glfwSetKeyCallback(window, glfw_callback_key);
    glfwSetWindowSizeCallback(window, glfw_callback_size);

    window_data_t* data = malloc(sizeof(window_data_t));
    if (!data)
    {
        errno_t error_number = errno;
        char error_str[100];
        strerror_s(error_str, 99, error_number);
        log_error("Can not allocate memory to window_data_t. %i: %s\n", error_number, error_str);
        glfwTerminate();
        return 0;
    }

    data->title = title;
    data->width = width;
    data->height = height;
    data->glfw_window = window;

    glfwSetWindowUserPointer(window, data);

    return data;
}

void window_end(window_data_t* window)
{
    glfwDestroyWindow(window->glfw_window);
    glfwTerminate();
    free(window);
}
