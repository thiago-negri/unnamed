#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "init.h"
#include "glfw_callbacks.h"

static int const width = 640;
static int const height = 480;
static char const* const title = "Unnamed";

GLFWwindow* init(void)
{
    glfwSetErrorCallback(glfw_callback_error);

    if (glfwInit() != GLFW_TRUE)
    {
        fputs("Could not initialize GLFW.\n", stderr);
        return NULL;
    }

	int glfw_major, glfw_minor, glfw_revision;
    glfwGetVersion(&glfw_major, &glfw_minor, &glfw_revision);
    fprintf(stdout, "GLFW %i.%i.%i (compiled with %i.%i.%i)\n", 
                    glfw_major, glfw_minor, glfw_revision, 
                    GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);

	GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        fputs("Could not open window.\n", stderr);
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);

	GLenum glew_init_result = glewInit();
	if (glew_init_result)
	{
		fputs("Could not initialize GLEW.\n", stderr);
		glfwTerminate();
		return NULL;
	}

	GLubyte const* gl_version = glGetString(GL_VERSION);
	fprintf(stdout, "OpenGL %s\n", gl_version);

    glfwSwapInterval(1);

    glfwSetKeyCallback(window, glfw_callback_key);

    return window;
}

