in vec2 in_Position;

uniform vec2 un_Position;

void main(void)
{
    gl_Position = vec4(un_Position.x + in_Position.x, un_Position.y + in_Position.y, 0.0, 1.0);
}

