#version 400 core

uniform float iTime;
uniform vec3 camPos;
uniform float xAngle;
uniform float yAngle;
uniform bool inside;
uniform vec3 lightdir;
in vec2 fragCoord;
out vec4 fragColor;

const float Scale = 1.3;
const vec3 Julia = vec3(-1.2, -2.0, -.6);
const float PI = 3.1416;
const float EPS = .0125;

mat2 rot;
float dist(vec3 p);

vec3 normal(vec3 pos)
{
	vec3 ex = vec3(0.01, 0.0, 0.0);
	vec3 ey = vec3(0.0, 0.01, 0.0);
	vec3 ez = vec3(0.0, 0.0, 0.01);
	return normalize(vec3(dist(pos + ex) - dist(pos - ex),
						dist(pos + ey) - dist(pos - ey),
						dist(pos + ez) - dist(pos - ez)));
}

float softshadow(in vec3 ro, in vec3 rd, float mint, float k)
{
	float res = 1.0;
	float t = mint;
	for(int i = 0; i < 32; i++)
	{
		float h = dist(ro + rd * t);
		h = max(h, 0.0);
		res = min(res, k * h / t);
		t += clamp(h, 0.01, 0.5);
	}
	return clamp(res, 0.0, 1.0);
}

float light(in vec3 p, in vec3 dir)
{
	vec3 ldir = normalize(lightdir);
	vec3 n = normal(p);
	float sh = softshadow(p, -ldir, .5, 20.);
	float diff = max(0., dot(ldir, -n));
	vec3 r = reflect(ldir, n);
	float spec = max(0., dot(dir, -r));
	return diff * sh + pow(spec, 30.) * .5 * sh + .15 * max(0., dot(normalize(dir), -n));   
}

mat3  rotationMatrix3(vec3 v, float angle)
{
	float c = cos(angle);
	float s = sin(angle);

	return mat3(c + (1.0 - c) * v.x * v.x, (1.0 - c) * v.x * v.y - s * v.z,
	(1.0 - c) * v.x * v.z + s * v.y,
	(1.0 - c) * v.x * v.y + s * v.z, c + (1.0 - c) * v.y * v.y,
	(1.0 - c) * v.y * v.z - s * v.x,
	(1.0 - c) * v.x * v.z - s * v.y, (1.0 - c) * v.y * v.z + s * v.x,
	c + (1.0 - c) * v.z * v.z);
}

//float dist (vec3 p)
//{
//	p = p.zxy;
//	//p.x *= .75;
//	vec3 anim = vec3(sin(1.), sin(iTime * .4), cos(iTime * .06));
//	p += sin(p * 3. + iTime * 2.) * .04;
//	mat3 rot = rotationMatrix3(normalize(vec3(0.5,-0.05,-0.5) + anim), 2 * PI / 3 + sin(iTime * 0.3) * 0.5);
//	vec3 pp = p;
//	float l;
//	for (int i = 0; i < 32; i++)
//	{
//		p.xy = abs(p.xy);
//		p = p * Scale + Julia;
//		p *= rot;
//		l = length(p);
//	}
//	return l * pow(Scale, -32);
//}

const float scale = 1.3;
const float bailout = 10.0;
#define CX 1.0
#define CY 1.0
#define CZ 1.0


float dist(vec3 p){
	int i;
	float r = dot(p, p);
	float tau = 0.436;
	mat2 rot = mat2(cos(tau), -sin(tau), sin(tau), cos(tau));
	for (i = 0; i < 32 && r < bailout; i++)
   {
		p.xz *= rot;
		float t;

		if (p.x < p.y) {t = p.y; p.y = p.x; p.x = t;}
		if (p.x < p.z) {t = p.z; p.z = p.x; p.x = t;}
		if (p.y < p.z) {t = p.z; p.z = p.y; p.y = t;}

		p.z -= 0.5 * CZ * (scale - 1.0) / scale;
		p.z = -abs(-p.z);
		p.z += 0.5 * CZ * (scale - 1.0) / scale;

		// rotate2(p);

		p.x = scale * p.x - CX * (scale - 1);
		p.y = scale * p.y - CY * (scale - 1);
		p.z *= scale;

		r = dot(p, p);
   }
   return length(p) * pow(scale, -i);
}

void main()
{
	vec2 uv = 2.0 * fragCoord - 1.0f;
	mat2 camRot;
	vec3 ro;
	vec3 rd;
	vec3 tmp = vec3(uv, 3.0);
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

	float st, d = 1.0, col, totdist = st = 0.0;
	vec3 p;
	for (int i = 0; i < 70; i++)
	{
		if (d > EPS && totdist < 50.)
		{
			p = ro + totdist * rd;
			d = dist(p);
			totdist += d;
		}
	}
	if (d < EPS)
		fragColor = vec4(vec3(light(p - EPS * rd, rd)), 1.0);
	else 
		fragColor = vec4(0.0);
}
