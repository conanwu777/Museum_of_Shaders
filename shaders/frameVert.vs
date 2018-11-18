#version 400 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 coord;

out vec2 fragCoord;
out vec2 TexCoord;

uniform bool far;
uniform bool swap;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 yaw;
uniform mat4 pitch;

void main()
{
	if (far)
		gl_Position = projection * yaw * pitch * view * vec4(aPos, 1.0);
	else
	{
		if (swap)
			gl_Position = vec4(aPos.z, (aPos.y - 1.4) , 0.0, 1.0);
		else
			gl_Position = vec4(aPos.x, (aPos.y - 1.4) , 0.0, 1.0);
	}
	fragCoord = coord;
}
