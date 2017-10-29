#include <stdio.h>

#include <GLFW/glfw3.h>

#include "init.h"

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

