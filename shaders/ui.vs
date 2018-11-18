#version 400 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 coord;

out vec2 fragCoord;
out vec2 TexCoord;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	fragCoord = coord;
}
