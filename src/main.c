#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window.h"
#include "shader.h"
#include "graphics.h"
#include "log.h"

static int const width = 640;
static int const height = 480;
static char const* const title = "Unnamed";

int main(int argc, char** argv)
{
    if (log_start())
    {
        return EXIT_FAILURE;
    }

    window_data_t* window = window_start(title, width, height);
    if (!window)
    {
        log_end();
        return EXIT_FAILURE;
    }

    shader_data_t shader = shader_create();
    if (!shader.program_id)
    {
        window_end(window);
        log_end();
        return EXIT_FAILURE;
    }

    graphics_start();

    graphics_data_t texture = graphics_load("res/image.bmp", 64, 64);
    if (!texture.texture_id)
    {
        shader_destroy(shader);
        window_end(window);
        log_end();
        return EXIT_FAILURE;
    }

    while (!glfwWindowShouldClose(window->glfw_window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        graphics_draw(window, shader, texture, 0.0f, 0.0f);
        graphics_draw(window, shader, texture, 1.0f, 1.0f);
        graphics_draw(window, shader, texture, 2.0f, 2.0f);
        graphics_draw(window, shader, texture, 3.0f, 3.0f);
        glfwSwapBuffers(window->glfw_window);
        glfwPollEvents();
    }

    graphics_unload(texture);

    graphics_end();

    shader_destroy(shader);
    window_end(window);
    log_end();

    return EXIT_SUCCESS;
}
