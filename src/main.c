#include <stdio.h>
#include <stdlib.h>

#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "init.h"
#include "shader.h"
#include "graphics.h"
#include "log.h"

int main(int argc, char** argv)
{
    if (log_start())
    {
        return EXIT_FAILURE;
    }

    GLFWwindow* window = init();
    if (!window)
    {
        log_end();
        return EXIT_FAILURE;
    }

    shader_data_t shader = shader_create();
    if (!shader.program_id)
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        log_end();
        return EXIT_FAILURE;
    }

    graphics_init();

    graphics_data_t texture = graphics_load("res/image.bmp", 64, 64);
    if (!texture.texture_id)
    {
        shader_destroy(shader);
        glfwDestroyWindow(window);
        glfwTerminate();
        log_end();
        return EXIT_FAILURE;
    }

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        graphics_draw(shader, texture, 0.0f, 0.0f);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    graphics_unload(texture);

    graphics_end();

    shader_destroy(shader);
    glfwDestroyWindow(window);
    glfwTerminate();
    log_end();
    return EXIT_SUCCESS;
}
