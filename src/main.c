#include <stdio.h>
#include <GLFW/glfw3.h>

static int width = 640;
static int height = 480;
static const char *title = "Hello, World";

int main(void)
{
    GLFWwindow *window;

    // Initialize GLFW
    if (glfwInit() != GLFW_TRUE)
    {
        fprintf(stderr, "Could not initialize GLFW.\n");
        return 1;
    }

    // Create window
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "Could not open window.\n");
        glfwTerminate();
        return 1;
    }

    // Display window
    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

