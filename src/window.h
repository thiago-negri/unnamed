#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct window_data window_data_t;

struct window_data
{
    char const* title;
    int width;
    int height;
    GLFWwindow* glfw_window;
};

window_data_t* window_start(char const* title, int width, int height);
void window_end(window_data_t* window_data);