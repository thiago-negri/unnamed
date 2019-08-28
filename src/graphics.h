#pragma once

#include <stdio.h>

#include <GL/glew.h>

#include "shader.h"

typedef struct graphics_data graphics_data_t;

struct graphics_data
{
    GLuint texture_id;
};

void graphics_init();
void graphics_end();

graphics_data_t graphics_load(unsigned char const* filepath, size_t width, size_t height);
void graphics_unload(graphics_data_t graphics_data);

void graphics_draw(shader_data_t shader, graphics_data_t graphics_data, GLfloat x, GLfloat y);