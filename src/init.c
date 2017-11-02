#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "init.h"
#include "glfw_callbacks.h"

static int width = 640;
static int height = 480;
static const char *title = "Unnamed";

GLFWwindow *init(void)
{
    GLenum glew_init_result;
    int glfw_major, glfw_minor, glfw_revision;
    GLFWwindow *window;

    glfwSetErrorCallback(glfw_callback_error);

    if (glfwInit() != GLFW_TRUE)
    {
        fprintf(stderr, "Could not initialize GLFW.\n");
        return NULL;
    }

    glfwGetVersion(&glfw_major, &glfw_minor, &glfw_revision);
    fprintf(stdout, "GLFW %i.%i.%i (compiled with %i.%i.%i)\n", glfw_major, glfw_minor, glfw_revision, GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "Could not open window.\n");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);

    fprintf(stdout, "OpenGL %s\n", glGetString(GL_VERSION));

    glew_init_result = glewInit();
    if (glew_init_result != GLEW_OK)
    {
        fprintf(stderr, "Could not initialize GLEW. %s\n", glewGetString(glew_init_result));
        glfwTerminate();
        return NULL;
    }

    fprintf(stdout, "GLEW %s\n", glewGetString(GLEW_VERSION));

    glfwSwapInterval(1);

    glfwSetKeyCallback(window, glfw_callback_key);

    return window;
}

