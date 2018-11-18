#version 400 core

uniform float iTime;
uniform vec3 camPos;
uniform float xAngle;
uniform bool inside;
uniform float yAngle;
in vec2 fragCoord;
out vec4 fragColor;

const vec3 lightdir = vec3(0.5, 1.0, 0.0);

#define PI 3.14159265359

float hash(float n){
	return fract(sin(n)*43758.5453);
}

float noise(in vec3 x)
{
	vec3 p = floor(x);
	vec3 f = fract(x);

	f = f * f * (3.0 - 2.0 * f);
	float n = p.x + p.y*57.0 + 113.0*p.z;
	float res = mix(mix(mix(hash(n + 0.0), hash(n + 1.0), f.x),
				mix(hash(n + 57.0), hash(n + 58.0), f.x), f.y),
				mix(mix(hash(n + 113.0), hash(n + 114.0), f.x),
				mix(hash(n + 170.0), hash(n + 171.0), f.x), f.y), f.z);
	return res;
}

float cloudNoise(float scale,in vec3 p, in vec3 dir)
{
	vec3 q = p + dir;
	float f;
	f  = 0.50000 * noise(q);
	q = q * scale * 2.02 + dir;
	f += 0.25000 * noise(q);
	q = q * 2.03 + dir;
	f += 0.12500 * noise(q);
	q = q * 2.01 + dir;
	f += 0.06250 * noise(q);
	q = q * 1.02 + dir;
	f += 0.03125 * noise(q);
	return f;
}

float sphere(vec3 p, float s) {
	return length(p) - s;
}

float dist(vec3 p)
{
	float f = cloudNoise(2, p, -vec3(0.0, 2.0, 1.0) * sin(iTime * 0.01));
	float den = sphere(p, 0.5);
	den = -smoothstep(-0.1, .25, den) - 0.45;
	return clamp(den + 1.5 * f, 0.0, 1.0);
}

float raymarch( in vec3 ro, in vec3 rd, in vec2 pixel)
{
	float sum = 0;
	float t = 0;

	for(int i = 0; i < 32; i++)
	{
		if (sum > 0.999)
			break ;
		vec3 pos = ro + t * rd;
		float d = dist(pos);
		float col = d * 3.;
		sum += col * (1.0 - sum);
		t += 0.07;
	}
	sum *= 0.9;
	return sum;
}

void main()
{
	vec2 uv = 2.0 * fragCoord - 1.0f;
	mat2 camRot;
	vec3 ro;
	vec3 rd;
	vec3 tmp = vec3(uv, 2.5);
	float camDist = 4;
	if (!inside)
	{
		ro = normalize(camPos) * camDist * 0.5;
		float an = PI * 0.5 - atan(camPos.z, camPos.x);
		camRot = mat2(cos(an), -sin(an), sin(an), cos(an));
		tmp.xz = camRot * tmp.xz;
		rd = -normalize(tmp);
	}
	else
	{
		ro = camPos * camDist;
		camRot = mat2(cos(-yAngle), -sin(-yAngle), sin(-yAngle), cos(-yAngle));
		tmp.yz = camRot * tmp.yz;
		camRot = mat2(cos(-xAngle), -sin(-xAngle), sin(-xAngle), cos(-xAngle));
		tmp.xz = camRot * tmp.xz;
		rd = normalize(tmp);
		rd.x *= -1.0;
	}
	fragColor = vec4(vec3(1., 0.95, 0.85), raymarch(ro, rd, uv));
}
