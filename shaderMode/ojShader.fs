#version 330 core
out vec4 FragColor;

in vec2 fragCoord;

void main()
{
    FragColor = vec4(vec3(1 - fragCoord.y / 2.0), 1.0);
} 