#version 400 core
uniform float iTime;
uniform vec3 camPos;
uniform float angle;
in vec2 fragCoord;
out vec4 fragColor;

const int Iterations=24;
const float Scale=1.3;
const vec3 Julia=vec3(-1.2,-2.0,-.6);
const vec3 RotVector=vec3(0.5,-0.05,-0.5);
const float RotAngle=66.;
const float Speed=0.5;
const float Amplitude=1.;
const float detail=.0125;
const vec3 lightdir=vec3(0.5,1.0,0.0);

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

float softshadow( in vec3 ro, in vec3 rd, float mint, float k )
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

float light(in vec3 p, in vec3 dir) {
	vec3 ldir = normalize(lightdir);
	vec3 n = normal(p);
	float sh = softshadow(p,-ldir, 1., 20.);
	float diff = max(0., dot(ldir, -n));
	vec3 r = reflect(ldir, n);
	float spec = max(0., dot(dir, -r));
	return diff * sh + pow(spec, 30.) * .5 * sh + .15 * max(0., dot(normalize(dir), -n));	
}

mat3  rotationMatrix3(vec3 v, float angle)
{
	float c = cos(radians(angle));
	float s = sin(radians(angle));
	
	return mat3(c + (1.0 - c) * v.x * v.x, (1.0 - c) * v.x * v.y - s * v.z,
		(1.0 - c) * v.x * v.z + s * v.y,
		(1.0 - c) * v.x * v.y + s * v.z, c + (1.0 - c) * v.y * v.y,
		(1.0 - c) * v.y * v.z - s * v.x,
		(1.0 - c) * v.x * v.z - s * v.y, (1.0 - c) * v.y * v.z + s * v.x,
		c + (1.0 - c) * v.z * v.z);
}

float dist(vec3 p) {
	p = p.zxy;

	p.x *= .75;
	float time = iTime * Speed;
	vec3 ani;
	ani = vec3(sin(1.), sin(time * .133), cos(time * .2)) * Amplitude;
	p += sin(p * 3. + time * 6.) * .04;
	mat3 rot = rotationMatrix3(normalize(RotVector + ani), RotAngle + sin(time) * 10.);
	vec3 pp = p;
	float l;
	for (int i = 0; i < Iterations; i++)
	{
		p.xy = abs(p.xy);
		p = p * Scale + Julia;
		p *= rot;
		l = length(p);
	}
	return l * pow(Scale, -float(Iterations)) * .9;
}

void main()
{
	vec2 uv = 2.0 * fragCoord - 1.0f;
	vec3 ro = (length(camPos) > 1.5 ? vec3(0.0, 0.0, 30) : camPos * 20);
	vec3 tmp = vec3(uv, 3.0);
	if (length(camPos) < 1.5)
	{
		mat2 camRot = mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
		tmp.xz = camRot * tmp.xz;
	}
	vec3 rd = -normalize(tmp);

	float st,d = 1.0, col, totdist = st = 0.0;
	vec3 p;
	for (int i = 0; i < 70; i++)
	{
		if (d > detail && totdist < 50.)
		{
			p = ro + totdist * rd;
			d = dist(p);
			totdist += d;
		}
	}
	if (d < detail)
		fragColor = vec4(vec3(light(p - detail * rd, rd)), 1.0);
	else 
		fragColor = vec4(0.0);
}
