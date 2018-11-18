#version 400 core

uniform float iTime;
uniform vec3 camPos;
uniform float xAngle;
uniform float yAngle;
uniform bool inside;
in vec2 fragCoord;
out vec4 fragColor;

#define PI 3.14159265359

void main()
{
	vec2 uv = fragCoord * 2 - 1;
	uv *= 0.4;
	float f = 0.0;
	float s = 0.0;
	if (!inside)
	{
		float t = iTime * .1;
		mat2 ma = mat2(cos(t), sin(t), -sin(t), cos(t));
		for (int i = 0; i < 150; i++)
		{
			vec3 p = s * vec3(uv, sin(iTime * 0.05));
			p.xy *= ma;
			p += vec3(.22, .3, s - 1.5 - sin(iTime * .02) * .1);
			for (int i = 0; i < 12; i++)
				p = abs(p) / dot(p, p) - 0.5;
			f += dot(p, p) * .0015 * (2. + sin(length(uv * 10.0)));
			s += .005;
		}
	}
	else
	{
		float t = iTime * .1 + xAngle * 0.5 / (length(uv) + .2);
		mat2 ma = mat2(cos(t), sin(t), -sin(t), cos(t));
		for (int i = 0; i < 150; i++)
		{
			vec3 p = s * vec3(uv, sin(iTime * 0.05) + camPos.z);
			p.xy *= ma;
			p += vec3(.22, .3, s - 1.5 - sin(iTime * .02) * .1);
			for (int i = 0; i < 12; i++)
				p = abs(p) / dot(p, p) - 0.5;
			f += dot(p, p) * .0015 * (2. + sin(length(uv * 10.0)));
			s += .005;
		}
	}

	float len = length(uv);
	vec3 col = vec3(f * 0.3, f * 0.4, f * 0.4 + 0.2) - 0.2;
	fragColor = vec4(min(abs(col), 1.0), 1.0);
}
