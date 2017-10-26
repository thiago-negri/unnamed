#include <stdio.h>
#include <GLFW/glfw3.h>

static int width = 640;
static int height = 480;
static const char *title = "Hello, World";

GLFWwindow *init(void);
void glfw_error_callback(int, const char *);

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

    glfwTerminate();
    return 0;
}

GLFWwindow *init(void)
{
    GLFWwindow *window;

    // Set GLFW error callback
    glfwSetErrorCallback(glfw_error_callback);

    // Initialize GLFW
    if (glfwInit() != GLFW_TRUE)
    {
        fprintf(stderr, "Could not initialize GLFW.\n");
        return NULL;
    }

    // Create window
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "Could not open window.\n");
        glfwTerminate();
        return NULL;
    }

    // Display window
    glfwMakeContextCurrent(window);

    return window;
}

void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "GLFW error %i: %s\n", error, description);
}

