#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>

#include "shader.h"

#include "loader.h"

// Convert shader type to string (human readable) representation
char const* _shader_type_str(GLenum shader_type)
{
    switch (shader_type) {
        case GL_VERTEX_SHADER:
            return "vertex";

        case GL_FRAGMENT_SHADER:
            return "fragment";
    }
    log_error("Unknown shader type used at _shader_type_str: %i\n", shader_type);
    return "unknown";
}

// Create a GL shader from a file
GLuint _shader_create_from_filepath(GLenum shader_type, char const* filepath)
{
    GLuint shader = glCreateShader(shader_type);
    if (!shader)
    {
        log_error("Can not create a shader.\n");
        return 0;
    }

    loader_file_data_t source = loader_load_filepath(filepath);
    if (!source.size)
    {
        glDeleteShader(shader);
        return 0;
    }

    glShaderSource(shader, 1, &source.content, &source.size);

    loader_unload(source);

    glCompileShader(shader);

    GLint compile_status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        char const* shader_type_str = _shader_type_str(shader_type);
        glGetShaderInfoLog(shader, 1024, &log_length, message);
        log_error("Could not compile %s shader '%s': %s\n", shader_type_str, filepath, message);
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

// Create GL program linking a vertex and a fragment shader
GLuint _shader_create_program(GLuint vertex_shader, GLuint fragment_shader)
{
    GLuint program = glCreateProgram();
    if (!program)
    {
        log_error("Can not create GL program.\n");
        return 0;
    }

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);

    GLint link_status;
    glGetProgramiv(program, GL_LINK_STATUS, &link_status);
    if (link_status != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetProgramInfoLog(program, 1024, &log_length, message);
        log_error("Could not link program: %s\n", message);
        glDeleteProgram(program);
        return 0;
    }

    return program;
}

// Create default GL program
shader_data_t shader_create()
{
    GLuint vertex_shader = _shader_create_from_filepath(GL_VERTEX_SHADER, "res/vertex_shader.vs");
    if (!vertex_shader)
    {
        return (shader_data_t) { 0 };
    }

    GLuint fragment_shader = _shader_create_from_filepath(GL_FRAGMENT_SHADER, "res/fragment_shader.fs");
    if (!fragment_shader)
    {
        glDeleteShader(vertex_shader);
        return (shader_data_t) { 0 };
    }

    GLuint program = _shader_create_program(vertex_shader, fragment_shader);

    GLint uniform_position = glGetUniformLocation(program, "un_Position");

    // Regardless of program linking correctly or not, shaders can be marked for deletion
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return (shader_data_t) {
        .program_id = program,
        .uniform_position = uniform_position
    };
}

void shader_destroy(shader_data_t shader)
{
    glDeleteProgram(shader.program_id);
}
