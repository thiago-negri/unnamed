#pragma once

#include <GL/glew.h>

typedef struct shader_data shader_data_t;

struct shader_data
{
    GLuint program_id;
    GLint uniform_position;
    GLint uniform_window_width;
    GLint uniform_window_height;
};

shader_data_t shader_create();
void shader_destroy(shader_data_t shader);
