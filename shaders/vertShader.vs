#version 400 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 coord;

out vec2 fragCoord;
out vec2 TexCoord;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 yaw;
uniform mat4 pitch;

void main()
{
	gl_Position = projection * yaw * pitch * view * vec4(aPos, 1.0);
	fragCoord = coord;
}
