#version 330 core
out vec4 FragColor;

in vec2 UV;

uniform sampler2D un_Texture;

void main(void)
{
    FragColor = texture(un_Texture, UV);
}