#version 400 core

uniform float iTime;
uniform vec3 camPos;
uniform float xAngle;
uniform float yAngle;
uniform bool inside;
uniform vec3 lightdir;
in vec2 fragCoord;
out vec4 fragColor;

#define STEPS 200
#define PI 3.14159265359
#define EPS 0.005
#define FAR 500.0

void sphereFold(inout vec3 z, inout float dz)
{
	float r2 = dot(z,z);
	if (r2 < 0.5)
	{ 
		float temp = 2.0;
		z *= temp;
		dz *= temp;
	}
	else if (r2 < 1.0)
	{ 
		float temp = 1.0 / r2;
		z *= temp;
		dz *= temp;
	}
}

void boxFold(inout vec3 z, inout float dz)
{
	z = clamp(z, -1.0, 1.0) * 2.0 - z;
}

float dist(vec3 z)
{
	mat2 rotation = mat2(cos(PI * 0.25), -sin(PI * 0.25),
	sin(PI * 0.25), cos(PI * 0.25));
	z.xy *= rotation;
	z.xz *= rotation;
	float scale = sin(iTime * 0.1) + 3.0;
	z *= 2 / scale;
	vec3 offset = z;
	float dr = 1.0;
	for (int n = 0; n < 12; n++)
	{
		boxFold(z, dr);
		sphereFold(z, dr);
		z = scale * z + offset;
		dr = dr * abs(scale) + 1.0;
	}
	float r = length(z);
	return r / abs(dr);
}

float shadow(in vec3 ro, in vec3 rd, in float hn)
{
	float res = 1.0;
	float t = 0.0005;
	float h = 1.0;
	for (int i = 0; i < 40; i++ )
	{
		h = dist(ro + rd * t);
		res = min(res, hn * h / t);
		t += clamp(h, 0.02, 2.0);
	}
	return clamp(res, 0.0, 1.0);
}

vec3 normal(vec3 pos)
{
	vec3 ex = vec3(0.01, 0.0, 0.0);
	vec3 ey = vec3(0.0, 0.01, 0.0);
	vec3 ez = vec3(0.0, 0.0, 0.01);
	return normalize(vec3(dist(pos + ex) - dist(pos - ex),
	dist(pos + ey) - dist(pos - ey),
	dist(pos + ez) - dist(pos - ez)));
}

float ambocc(vec3 pos, vec3 nor)
{
	float occ = 0.0;
	float sca = 1.0;
	for(int i = 0; i < 5; i++)
	{
		float hr = 0.01 + 0.12 * float(i) / 4.0;
		vec3 aopos = nor * hr + pos;
		float dd = dist(aopos);
		occ += -(dd - hr) * sca;
		sca *= 0.95;
	}
	return clamp(1.0 - 3.0 * occ, 0.0, 1.0 );
}

vec3 light(vec3 lightdir, vec3 lightcol, vec3 tex, vec3 norm, vec3 camdir)
{
	float cosa = pow(0.5 + 0.5 * dot(norm, -lightdir), 2.0);
	float cosr = max(dot(-camdir, reflect(lightdir, norm)), 0.0);
	float diffuse = cosa;
	float phong = pow(cosr, 8.0);
	return lightcol * (tex * diffuse + phong);
}

vec3 material(vec3 pos, vec3 camdir)
{
	vec3 norm = normal(pos);
	float ao = ambocc(pos, norm);
	vec3 d1 = lightdir;
	vec3 d2 = lightdir.zyx;
	vec3 tex = vec3(0.8, 0.7, 0.4);
	vec3 l1 = light(d1, vec3(0.8, 0.7, 0.6), tex, norm, camdir);
	vec3 l2 = light(d2, vec3(0.8, 0.7, 0.6), tex, norm, camdir);
	float sha = 0.7 * shadow(pos, -lightdir, 32.0);
	return 0.5 * ao + (1.4 * l1 + l2) * sha;
}

vec3 rayrender(vec3 pos, vec3 dir, float dist)
{
	vec3 col = vec3(0.0);
	vec3 inters = pos + dist * dir;
	col = material(inters, dir);
	return col;
}

void main()
{
	vec2 uv = 2.0 * fragCoord - 1.0f;
	mat2 camRot;
	vec3 ro;
	vec3 rd;
	vec3 tmp = vec3(uv, 2.5);
	float camDist = 60;
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
	float t = 0.0, d = 0.0;
	for (int i = 0; i < STEPS; ++i)
	{
		d = dist(ro + t * rd);
		if (d < EPS || t > FAR)
		break;
		t += d;
	}
	if (d < EPS)
		fragColor = vec4(rayrender(ro + (t - EPS) * rd, rd, d), 1.0);
	else 
		fragColor = vec4(0.0);
}
