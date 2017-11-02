#include "shader.h"

#include <stdio.h>
#include <stdlib.h>

#include "loader.h"

GLuint shader_create()
{
    GLuint program;
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLint vertex_compile_status;
    GLint fragment_compile_status;
    GLint program_link_status;
    char *vertex_shader_source;
    char *fragment_shader_source;

    // Create objects
    program = glCreateProgram();
    if (program == 0)
        return 0;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    if (vertex_shader == 0)
    {
        glDeleteProgram(program);
        return 0;
    }

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    if (fragment_shader == 0)
    {
        glDeleteShader(vertex_shader);
        glDeleteProgram(program);
        return 0;
    }

    // Compile shaders
    vertex_shader_source = loader_load_filepath("res/vertex_shader.vs");
    if (vertex_shader_source == NULL)
    {
        glDeleteShader(vertex_shader);
        glDeleteProgram(program);
        return 0;
    }

    glShaderSource(vertex_shader, 1, (const GLchar **) &vertex_shader_source, NULL);

    free(vertex_shader_source);

    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vertex_compile_status);
    if (vertex_compile_status != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetShaderInfoLog(vertex_shader, 1024, &log_length, message);
        fprintf(stderr, "Could not compile vertex shader: %s\n", message);
        glDeleteShader(fragment_shader);
        glDeleteShader(vertex_shader);
        glDeleteProgram(program);
        return 0;
    }

    fragment_shader_source = loader_load_filepath("res/fragment_shader.fs");
    if (fragment_shader_source == NULL)
    {
        glDeleteShader(fragment_shader);
        glDeleteShader(vertex_shader);
        glDeleteProgram(program);
        return 0;
    }

    glShaderSource(fragment_shader, 1, (const GLchar **) &fragment_shader_source, NULL);

    free(fragment_shader_source);

    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &fragment_compile_status);
    if (fragment_compile_status != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetShaderInfoLog(fragment_shader, 1024, &log_length, message);
        fprintf(stderr, "Could not compile fragment shader: %s\n", message);
        glDeleteShader(fragment_shader);
        glDeleteShader(vertex_shader);
        glDeleteProgram(program);
        return 0;
    }

    // Link program
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &program_link_status);
    if (program_link_status != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetProgramInfoLog(program, 1024, &log_length, message);
        fprintf(stderr, "Could not link program: %s\n", message);
        glDeleteShader(fragment_shader);
        glDeleteShader(vertex_shader);
        glDeleteProgram(program);
        return 0;
    }

    // Flag shaders for deletion
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

