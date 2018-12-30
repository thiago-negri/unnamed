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
    fprintf(stderr, "Unknown shader type used at _shader_type_str: %i\n", shader_type);
    return "unknown";
}

// Create a GL shader from a file
GLuint _shader_create_from_filepath(GLenum shader_type, char const* filepath)
{
    GLuint shader = glCreateShader(shader_type);
	if (shader == 0)
	{
		fputs("Can not create a shader.\n", stderr);
		return 0;
	}

    char* source = loader_load_filepath(filepath);
    if (source == NULL)
    {
        glDeleteShader(shader);
        return 0;
    }

    glShaderSource(shader, 1, (GLchar const **) &source, NULL);

    free(source);

    glCompileShader(shader);

	GLint compile_status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
		char const* shader_type_str = _shader_type_str(shader_type);
        glGetShaderInfoLog(shader, 1024, &log_length, message);
        fprintf(stderr, "Could not compile %s shader '%s': %s\n", shader_type_str, filepath, message);
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

// Create GL program linking a vertex and a fragment shader
GLuint _shader_create_program(GLuint vertex_shader, GLuint fragment_shader)
{
	GLuint program = glCreateProgram();
    if (program == 0)
    {
		fputs("Can not create GL program.\n", stderr);
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
        fprintf(stderr, "Could not link program: %s\n", message);
        glDeleteProgram(program);
        return 0;
    }

    return program;
}

// Create default GL program
GLuint shader_create()
{
	GLuint vertex_shader = _shader_create_from_filepath(GL_VERTEX_SHADER, "res/vertex_shader.vs");
    if (vertex_shader == 0)
    {
        return 0;
    }

	GLuint fragment_shader = _shader_create_from_filepath(GL_FRAGMENT_SHADER, "res/fragment_shader.fs");
    if (fragment_shader == 0)
    {
        glDeleteShader(vertex_shader);
        return 0;
    }

	GLuint program = _shader_create_program(vertex_shader, fragment_shader);

    // Regardless of program linking correctly or not, shaders can be marked for deletion
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}
