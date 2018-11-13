#version 400 core

#define PI 3.14159265359
uniform float iTime;
uniform vec3 camPos;
uniform float angle;
in vec2 fragCoord;
out vec4 fragColor;

float hash( float n )
{
    return fract(sin(n)*43758.5453);
}

float noise(in vec3 x)
{
    vec3 p = floor(x);
    vec3 f = fract(x);

    f = f*f*(3.0-2.0*f);

    float n = p.x + p.y*57.0 + 113.0*p.z;

    float res = mix(mix(mix( hash(n+  0.0), hash(n+  1.0),f.x),
                        mix( hash(n+ 57.0), hash(n+ 58.0),f.x),f.y),
                    mix(mix( hash(n+113.0), hash(n+114.0),f.x),
                        mix( hash(n+170.0), hash(n+171.0),f.x),f.y),f.z);
    return res;
}

float cloudNoise(float scale,in vec3 p, in vec3 dir)
{
	vec3 q = p + dir; 
    float f;
	f  = 0.50000*noise( q ); q = q*scale*2.02 + dir;
    f += 0.25000*noise( q ); q = q*2.03 + dir;
    f += 0.12500*noise( q ); q = q*2.01 + dir;
    f += 0.06250*noise( q ); q = q*2.02 + dir;
    f += 0.03125*noise( q );
    return f;
}

float sdSphere(vec3 p, float s)
{
  return length(p) - s;
}

float sdBox( vec3 p, vec3 b )
{
  vec3 d = abs(p) - b;
  return min(max(d.x,max(d.y,d.z)),0.0) + length(max(d,0.0));
}

float map( vec3 p )
{
	float f = cloudNoise(2, p, -vec3(0.0, 2.0, 1.0) * sin(iTime * 0.01));
	float den = sdSphere(p, 0.5);
    den = -smoothstep(-0.1, .25,den) - 0.45;
	return clamp(den + 1.5 * f, 0.0, 1.0 );
}

vec4 raymarch( in vec3 ro, in vec3 rd, in vec2 pixel )
{
	vec4 sum = vec4( 0.0 );

	float t = 0;
	
	for(int i = 0; i < 32; i++)
	{
		if (sum.a > 0.999)
			break;
		vec3 pos = ro + t * rd;
        float d = map(pos);
		vec4 col = vec4(mix(vec3(1.0, 1.0, 1.1), vec3(1.2, 1.2, 0.8), d), 1.0);
		col *= d * 6.;
		sum += col * (1.0 - sum.a);	
		t += 0.07;
	}
	sum.a *= 0.8;
	sum.xyz = clamp(sum.xyz, 0.0, 1.0);
	return sum;
}


void main()
{
	vec2 uv = 2.0 * fragCoord - 1.0f;
	vec3 ro;
	mat2 camRot;
	if (length(camPos) > 1.5)
	{
		ro = normalize(camPos) * 1.5;
		float an = PI * 0.5 - atan(camPos.z, camPos.x);
		camRot = mat2(cos(an), -sin(an), sin(an), cos(an));
	}
	else
	{
		ro = camPos;
		camRot = mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
	}
	vec3 tmp = vec3(uv, 2.5);
	tmp.xz = camRot * tmp.xz;
	vec3 rd = -normalize(tmp);
    //light
	fragColor = raymarch( ro, rd, uv );
}
