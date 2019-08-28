#include <stdio.h>
#include <stdlib.h>

#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "init.h"
#include "shader.h"
#include "graphics.h"

int main(int argc, char** argv)
{
    GLFWwindow* window = init();
    if (!window)
    {
        return EXIT_FAILURE;
    }

    shader_data_t shader = shader_create();
    if (!shader.program_id)
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    graphics_init();

    graphics_data_t texture = graphics_load("res/image.bmp", 64, 64);
    if (!texture.texture_id)
    {
        shader_destroy(shader);
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        graphics_draw(shader, (graphics_data_t) { 0 }, -0.5f, -0.5f);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    graphics_unload(texture);

    graphics_end();

    shader_destroy(shader);
    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
}
