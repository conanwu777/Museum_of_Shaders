#version 400 core
uniform float iTime;
uniform vec3 camPos;
uniform float angle;
in vec2 fragCoord;
out vec4 fragColor;

#define STEPS 100
#define PI 3.14159265359
#define EPS 0.01
#define FAR 500.0

void sphereFold(inout vec3 z, inout float dz)
{
	float r2 = dot(z,z);
	if (r2 < 0.5)
	{ 
		float temp = 2.0;
		z *= temp;
		dz*= temp;
	}
	else if (r2 < 1.0)
	{ 
		float temp = 1.0 / r2;
		z *= temp;
		dz*= temp;
	}
}

void boxFold(inout vec3 z, inout float dz)
{
	z = clamp(z, -1.0, 1.0) * 2.0 - z;
}

float dist(vec3 z)
{
	mat2 rotation = mat2(cos(PI * 0.25), -sin(PI * 0.25), sin(PI * 0.25), cos(PI * 0.25));
	z.xy *= rotation;
	z.xz *= rotation;
	float scale = sin(iTime * 0.1) + 3.0;
	vec3 offset = z;
	float dr = 1.0;
	for (int n = 0; n < 10; n++)
	{
		boxFold(z,dr);
		sphereFold(z,dr);
		z = scale * z + offset;
		dr = dr * abs(scale) + 1.0;
	}
	float r = length(z);
	return r / abs(dr);
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
	vec3 d3 = vec3(-0.94281, -0.23570, 0.23570);
	vec3 d4 = vec3(0.94281, -0.23570, -0.23570);
	vec3 tex = vec3(0.32,0.28,0.0);
	vec3 l1 = light(d1, vec3(1.0,0.9,0.8), tex, norm, camdir);
	vec3 l2 = light(d2, vec3(0.8,0.7,0.6), tex, norm, camdir);
	vec3 l3 = light(d3, vec3(0.3,0.3,0.4), tex, norm, camdir);
	vec3 l4 = light(d4, vec3(0.5,0.5,0.5), tex, norm, camdir);
	return 0.5 * ao + 0.5 * (l1 + l2 + l3 + l4);
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
	vec3 ro = (length(camPos) > 1.5 ? vec3(0.0, 0.0, 30) : camPos * 20);
	vec3 tmp = vec3(uv, 2.5);
	if (length(camPos) < 1.5)
	{
		mat2 camRot = mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
		tmp.xz = camRot * tmp.xz;
	}
	vec3 rd = -normalize(tmp);

	float dist = raymarcher(ro, rd);
	vec3 col = rayrender(ro, rd, dist);

	col = pow(col, vec3(1.0));
	fragColor = vec4(dist == -1 ? vec3(0.0) : col, 1.0);
}
