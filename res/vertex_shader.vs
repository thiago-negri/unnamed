#version 330 core

in vec2 in_Position;
in vec2 in_UV;

out vec2 UV;

uniform vec2 un_Position;

void main(void)
{
    gl_Position = vec4(un_Position.x + in_Position.x, un_Position.y + in_Position.y, 0.0, 1.0);
    UV = in_UV;
}

