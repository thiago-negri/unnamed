#include "shader.h"

#include <stdio.h>
#include <stdlib.h>

#include "loader.h"

// Convert shader type to string (human readable) representation
const char *_shader_type_str(GLenum shader_type)
{
    switch (shader_type) {
        case GL_VERTEX_SHADER:   return "vertex";
        case GL_FRAGMENT_SHADER: return "fragment";
    }
    fprintf(stderr, "Unknown shader type used at _shader_type_str: %i\n", shader_type);
    return "unknown";
}

// Create a GL shader from a file
GLuint _shader_create_from_filepath(GLenum shader_type, const char *filepath)
{
    GLuint shader;
    char *source;
    GLint compile_status;

    shader = glCreateShader(shader_type);
    if (shader == 0) return 0;

    source = loader_load_filepath(filepath);
    if (source == NULL)
    {
        glDeleteShader(shader);
        return 0;
    }

    glShaderSource(shader, 1, (const GLchar **) &source, NULL);

    free(source);

    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetShaderInfoLog(shader, 1024, &log_length, message);
        fprintf(stderr, "Could not compile %s shader '%s': %s\n", _shader_type_str(shader_type), filepath, message);
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

// Create GL program linking a vertex and a fragment shader
GLuint _shader_create_program(GLuint vertex_shader, GLuint fragment_shader)
{
    GLuint program;
    GLint link_status;

    program = glCreateProgram();
    if (program == 0)
    {
        return 0;
    }

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &link_status);
    if (link_status != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetProgramInfoLog(program, 1024, &log_length, message);
        fprintf(stderr, "Could not link program: %s\n", message);
        glDeleteProgram(program);
        return 0;
    }

    return program;
}

// Create default GL program
GLuint shader_create()
{
    GLuint program;
    GLuint vertex_shader;
    GLuint fragment_shader;

    vertex_shader = _shader_create_from_filepath(GL_VERTEX_SHADER, "res/vertex_shader.vs");
    if (vertex_shader == 0)
    {
        return 0;
    }

    fragment_shader = _shader_create_from_filepath(GL_FRAGMENT_SHADER, "res/fragment_shader.fs");
    if (fragment_shader == 0)
    {
        glDeleteShader(vertex_shader);
        return 0;
    }

    program = _shader_create_program(vertex_shader, fragment_shader);

    // Regardless of program linking correctly or not, shaders can be marked for deletion
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

