#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glfw_callbacks.h"

static int width = 640;
static int height = 480;
static const char *title = "Hello, World";

GLFWwindow *init(void);

int main(void)
{
    GLFWwindow *window;

    window = init();

    if (window == NULL)
        return 1;

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}

GLFWwindow *init(void)
{
    GLenum glew_init_result;
    int glfw_major, glfw_minor, glfw_revision;
    GLFWwindow *window;

    glfwSetErrorCallback(glfw_error_callback);

    if (glfwInit() != GLFW_TRUE)
    {
        fprintf(stderr, "Could not initialize GLFW.\n");
        return NULL;
    }

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "Could not open window.\n");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);

    glew_init_result = glewInit();
    if (glew_init_result != GLEW_OK)
    {
        fprintf(stderr, "Could not initialize GLEW. %s\n", glewGetString(glew_init_result));
        glfwTerminate();
        return NULL;
    }

    glfwSwapInterval(1);

    fprintf(stdout, "GL %s\n", glGetString(GL_VERSION));

    glfwGetVersion(&glfw_major, &glfw_minor, &glfw_revision);
    fprintf(stdout, "GLFW %i.%i.%i (compiled with %i.%i.%i)\n", glfw_major, glfw_minor, glfw_revision, GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);

    fprintf(stdout, "GLEW %s\n", glewGetString(GLEW_VERSION));

    return window;
}

