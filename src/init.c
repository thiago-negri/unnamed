#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "init.h"
#include "glfw_callbacks.h"
#include "log.h"

static int const width = 640;
static int const height = 480;
static char const* const title = "Unnamed";

GLFWwindow* init(void)
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

    return window;
}

