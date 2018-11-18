#version 400 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 coord;

out vec2 fragCoord;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 yaw;
uniform mat4 pitch;

uniform float x;
uniform float z;
uniform bool far;

mat4 M = mat4(
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	x, 0.0, z, 1.0);

void main()
{
	mat4 ModelView = yaw * pitch * view * M;

	ModelView[0][0] = 1;
	ModelView[0][1] = 0;
	ModelView[0][2] = 0;

	ModelView[2][0] = 0;
	ModelView[2][1] = 0;
	ModelView[2][2] = 1;

	if (far)
		gl_Position = projection * ModelView * vec4(aPos, 1.0);
	else
		gl_Position = vec4(aPos* 2, 1.0);
	fragCoord = coord;
}
