#version 400 core
#define STEPS 100
#define EPS 0.0005
#define FAR 20.0
#define PI 3.14159265359
#define Scale 2.0
#define Bailout 1.25
#define Power 10.0

uniform float iTime;
uniform vec3 camPos;
uniform float angle;

in vec2 fragCoord;
out vec4 fragColor;

float dist(vec3 pos) {
	vec3 z = pos;
	float theta = fract(iTime * 0.01) * 2 * PI;
	mat2 rotation = mat2(cos(theta), -sin(theta), sin(theta), cos(theta));
	z.xz *= rotation;
	z.yz *= rotation;
	float dr = 1.0;
	float r = 0.0;
	for (int i = 0; i < 10 ; i++)
	{
		r = length(z);
		if (r > Bailout)
			break;
		float theta = acos(z.z/r);
		float phi = atan(z.y,z.x);
		dr =  pow( r, Power-1.0)*Power*dr + 1.0;

		float zr = pow( r,Power);
		theta = theta*Power;
		phi = phi*Power;

		z = zr*vec3(sin(theta)*cos(phi), sin(phi)*sin(theta), cos(theta));
		z += pos;
	}
	return 0.5 * log(r) * r/dr;
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
		occ += -(dd-hr) * sca;
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

	vec3 d1 = vec3(-0.21821, -0.43643, 0.87287);
	vec3 d2 = vec3(0.21821, -0.43643, -0.87287);
	vec3 tex = vec3(0.32,0.32,0.28);
	vec3 l1 = light(d1, vec3(1.0,0.9,0.8), tex, norm, camdir);
	vec3 l2 = light(d2, vec3(0.8,0.7,0.6), tex, norm, camdir);
	return 0.5 * ao + 1.0 * (l1 + l2);
}

vec3 rayrender(vec3 pos, vec3 dir, float dist)
{
	vec3 col = vec3(0.0);

	vec3 inters = pos + dist * dir;
	col = material(inters, dir);
	return col;
}

float raymarcher(vec3 ro, vec3 rd)
{
	float h = EPS * 2.0;
	float t = 0.0;
	float res = -1.0;
	for (int i = 0; i < STEPS; i++)
	{
		if (h < EPS || t > FAR)
			break ;
		h = dist(ro + rd * t);
		t += h * 1.0;
	}
	if (t < FAR)
		res = t;
	return res;
}

void main()
{
	vec2 uv = 2.0 * fragCoord - 1.0f;
	vec3 ro;
	mat2 camRot;
	if (length(camPos) > 1.5)
	{
		ro = normalize(camPos) * 1.5;
		float an = acos(dot(normalize(-camPos.xz), vec2(0.0, -1.0)));
		camRot = mat2(cos(an), -sin(an), sin(an), cos(an));
	}
	else
	{
		ro = camPos;
		camRot = mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
	}
	vec3 tmp = vec3(uv, 0.8);
	tmp.xz = camRot * tmp.xz;
	vec3 rd = -normalize(tmp);
	float t = 0.0, d = 0.0;
	for (int i = 0; i < STEPS; ++i)
	{
		d = dist(ro + t * rd);
		if (d < EPS || t > FAR) break;
		t += d;
	}
	fragColor = vec4(rayrender(ro + t * rd, rd, d), d < EPS ? 1.0 : 0.0);
}
