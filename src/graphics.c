#include <stdio.h>

#include <GL/glew.h>

#include "loader.h"
#include "shader.h"
#include "graphics.h"

static GLuint default_vao_id;
static GLuint default_vbo_id;

void graphics_init()
{
    GLfloat data[] = {
        // positions      // uv coordinates
        -0.5f, -0.5f,     0.0f, 0.0f,         // bottom left
        -0.5f,  0.5f,     0.0f, 1.0f,         // top left
         0.5f,  0.5f,     1.0f, 1.0f,         // top right
         0.5f, -0.5f,     1.0f, 0.0f,         // bottom right
        -0.5f, -0.5f,     0.0f, 0.0f,         // bottom left
         0.5f,  0.5f,     1.0f, 1.0f          // top right
    };

    glGenVertexArrays(1, &default_vao_id);
    glBindVertexArray(default_vao_id);

    glGenBuffers(1, &default_vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, default_vbo_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);

    // size of a vertex
    GLsizei stride = 4 * sizeof(GLfloat);

    // 1st attribute, 2 floats for position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid const*) 0);
    glEnableVertexAttribArray(0);

    // 2nd attribute, 2 floats for uv coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid const*) (2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void graphics_end()
{
    glDeleteBuffers(1, &default_vbo_id);
    glDeleteVertexArrays(1, &default_vao_id);

    default_vbo_id = 0;
    default_vao_id = 0;
}

graphics_data_t graphics_load(unsigned char const* filepath, size_t width, size_t height)
{
    loader_file_data_t image = loader_load_filepath(filepath);
    if (!image.size)
    {
        return (graphics_data_t) { 0 };
    }

    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, width, height);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, image.content);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    loader_unload(image);

    return (graphics_data_t) { .texture_id = texture_id };
}

void graphics_unload(graphics_data_t graphics_data)
{
    glDeleteTextures(1, &graphics_data.texture_id);
}

void graphics_draw(shader_data_t shader, graphics_data_t graphics_data, GLfloat x, GLfloat y)
{
    glUseProgram(shader.program_id);
    glUniform2f(shader.uniform_position, x, y);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, graphics_data.texture_id);

    glBindVertexArray(default_vao_id);
    glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}