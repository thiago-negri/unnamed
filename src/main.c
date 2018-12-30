#include <stdio.h>
#include <stdlib.h>

#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "init.h"
#include "shader.h"

int main(void)
{
    GLFWwindow* window = init();
    if (window == NULL)
    {
        return EXIT_FAILURE;
    }

    GLuint program = shader_create();
    if (program == 0)
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glUseProgram(program);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(program);
    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
}
