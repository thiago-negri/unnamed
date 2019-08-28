#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void glfw_callback_error(int error, char const* description);
void glfw_callback_key(GLFWwindow* window, int key, int scancode, int action, int mods);
void glfw_callback_size(GLFWwindow* window, int width, int height);
