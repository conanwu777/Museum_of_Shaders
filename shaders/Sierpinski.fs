#version 400 core

uniform float iTime;
uniform vec3 camPos;
uniform float xAngle;
uniform float yAngle;
uniform bool inside;
uniform vec3 lightdir;
in vec2 fragCoord;
out vec4 fragColor;

#define STEPS 100
#define PI 3.14159265359
#define EPS 0.005
#define FAR 500.0
#define Scale 2.0

float dist(vec3 z)
{
	float theta = fract(iTime * 0.01) * 2 * PI;
	mat2 rotation = mat2(cos(theta), -sin(theta), sin(theta), cos(theta));
	z.xy *= rotation;
	z.xz *= rotation;
	vec3 a1 = vec3(1, 1, 1);
	vec3 a2 = vec3(-1, -1, 1);
	vec3 a3 = vec3(1, -1, -1);
	vec3 a4 = vec3(-1, 1, -1);
	vec3 c;
	int n = 0;
	float dist, d;
	while (n < 10) {
		c = a1;
		dist = length(z - a1);
		d = length(z - a2); if (d < dist) {c = a2; dist = d;}
		d = length(z - a3); if (d < dist) {c = a3; dist = d;}
		d = length(z - a4); if (d < dist) {c = a4; dist = d;}
		z = Scale * z - c * (Scale - 1.0);
		n++;
	}
	return length(z) * pow(Scale, float(-n));
}

float raymarcher(vec3 ro, vec3 rd)
{
	float h = EPS * 2.0;
	float t = 0.0;
	float res = -1.0;
	for (int i = 0; i < STEPS; i++)
	{
		if (h < EPS || t > FAR)
			break;
		h = dist(ro + rd * t);
		t += h * 1.0;
	}
	if (t < FAR)
		res = t;
	return res;
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
	return clamp(1.0 - 3.0 * occ, 0.0, 1.0);
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
	vec3 tex = vec3(.5, .5, 0.5);
	vec3 l1 = light(d1, vec3(.8, .8, .4), tex, norm, camdir);
	vec3 l2 = light(d1, vec3(.5, .5, .3), tex, norm, camdir);
	return 0.5 * ao + l1 + 0.3 * l2;
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
	float camDist = 10;
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
	float dist = raymarcher(ro, rd);
	if (dist >= 0)
		fragColor = vec4(rayrender(ro, rd, dist), 1.0);
	else 
		fragColor = vec4(0.0);
	vec3 col = rayrender(ro, rd, dist);
	col = pow(col, vec3(1.0));
	fragColor = vec4(col, dist == -1 ? 0.0 : 1.0);
}
