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
	vec2 uv = 2.0 * fragCoord - 1.0f;
	vec2 p = uv * 0.4;

	float an = mod(iTime * 0.1, 2. * PI);
	mat2 rot = mat2(cos(an), -sin(an), sin(an), cos(an));
	p *= rot;
	float an2 = atan(p.y, p.x) * 2.;
	p = length(p) * vec2(cos(an2), sin(an2));

	fragColor *= 0.;
	for (int i = 0; i < (inside ? 10 - camPos.z : 10); i++)
	{
		p = abs(2. * fract(p - .5) - 1.)
		* mat2(cos(iTime * .02 * float(i) + .3 * vec4(3, 7, 1, 0))),
		fragColor += exp(-(abs(p.y + p.x)) * 2.)
		* (cos(vec4(3, 2, 1, 0) * float(i)) * .5 + .5);
	}
	fragColor.r *= 0.7;
	fragColor.g *= .5;
	fragColor.b = 0.2;
	fragColor -= length(uv);
	fragColor.a = 1.0;
}
