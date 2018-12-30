#include <stdio.h>

#include "glfw_callbacks.h"

void glfw_callback_error(int error, char const* description)
{
    fprintf(stderr, "GLFW error %i: %s\n", error, description);
}

void glfw_callback_key(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}
