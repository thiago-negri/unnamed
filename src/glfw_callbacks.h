#pragma once

#include <GLFW/glfw3.h>

void glfw_callback_error(int error, const char *description);
void glfw_callback_key(GLFWwindow *window, int key, int scancode, int action, int mods);

