#version 400 core

uniform float iTime;
uniform vec3 camPos;
uniform float xAngle;
uniform float yAngle;
uniform bool inside;
in vec2 fragCoord;
out vec4 fragColor;

#define PI 3.14159265359
#define JULIA_IT 10
#define STEPS 200
#define EPS 0.001
#define NORMAL_STEP 0.0001

#define BURN_THRESH 0.90
#define BURN_INTENSITY 4.0

#define T sin(iTime * 0.1)

vec4 quat_mul (vec4 a, vec4 b) {
	return vec4 (
	a.x * b.x - a.y * b.y - a.z * b.z - a.w * b.w,
	a.x * b.y + a.y * b.x - a.z * b.w + a.w * b.z,
	a.x * b.z + a.y * b.w + a.z * b.x - a.w * b.y,
	a.x * b.w - a.y * b.z + a.z * b.y + a.w * b.x );
}

float dist(vec4 coor) {
	vec4 derivative = vec4(1.0);
	for (int i = 0; i < JULIA_IT; i++)
	{
		derivative = 2.0 * quat_mul(coor, derivative);
		coor = quat_mul(coor, coor) + vec4(0.5, 0.6, 0.10, 0.0);
		if (dot(coor, coor) > 4.0)
			break;
	}
	return sqrt(dot(coor, coor) / dot(derivative, derivative))
	* log(sqrt(dot(coor, coor)));
}

vec4 normal (vec4 coords)
{
	return normalize(vec4(
		dist(coords+vec4(-NORMAL_STEP, 0.0, 0.0, T)) -
		dist(coords+vec4(NORMAL_STEP, 0.0, 0.0, T)),
		dist(coords+vec4(0.0, -NORMAL_STEP, 0.0, T)) -
		dist(coords+vec4(0.0, NORMAL_STEP, 0.0, T)),
		dist(coords+vec4(0.0, 0.0, -NORMAL_STEP, T)) -
		dist(coords+vec4(0.0, 0.0, NORMAL_STEP, T)),
		0.0));
}

bool raycast_distance(vec3 ray, vec3 origin, out vec3 n)
{
	vec4 derivative;
	vec3 pos = origin;
	derivative = vec4(1.0);

	for (int i = 0; i < STEPS; i++) {
		float dist = dist(vec4(pos, T));
		pos += ray * dist;
		if (dist < EPS)
		{
			n = -normal(vec4(pos, 0.0)).xyz;
			return true;
		}
		if (dot(pos, pos) > 40.0)
			break ;
	}
	return false ;
}

vec3 env(vec3 at)
{
	vec3 map = vec3(2.2);
	return mix(map, BURN_THRESH + BURN_INTENSITY * smoothstep(vec3(BURN_THRESH), vec3(1.0), map), step(vec3(BURN_THRESH), map));
}

float fresnel(float r0, float cosine) {
	if (cosine < 0.0)
		return 0.0;
	return mix(r0, 1.0, pow(1.0 - cosine, 5.0));
}

void main()
{
	vec2 uv = 2.0 * fragCoord - 1.0f;
	mat2 camRot;
	vec3 ro;
	vec3 rd;
	vec3 tmp = vec3(uv, 2.0);
	float camDist = 6;
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
	vec3 normal;
	bool b = raycast_distance(rd, ro, normal);
	if (!b)
	{
		fragColor.a = 0.0;
		return ;
	}
	vec3 col = mix(vec3(0.0), env(reflect(rd, normal)),
	fresnel(0.0, dot(normal, -rd)));
	col = pow(col, vec3(0.5, 0.2, 0.3)) * vec3(1.1, 1.0, 1.0) + vec3(0.0, 0.0, 0.02);
	fragColor = vec4(pow(col, vec3(1.0/2.2)), clamp(length(col.rgb), 0, 0.4) + 0.5);
}
