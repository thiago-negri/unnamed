#version 330 core

in vec2 in_Position;
in vec2 in_UV;

out vec2 UV;

uniform vec2 un_Position;
uniform int un_WindowWidth;
uniform int un_WindowHeight;

void main(void)
{
    float unit_size = 32;
    float width_capacity = un_WindowWidth / unit_size;
    float height_capacity = un_WindowHeight / unit_size;

    float x = -1.0 + (1.0 + un_Position.x * 2.0 + in_Position.x) / width_capacity;
    float y = 1.0 - (un_Position.y * 2.0 + (1.0 - in_Position.y)) / height_capacity;

    gl_Position = vec4(x, y, 0.0, 1.0);
    UV = in_UV;
}

