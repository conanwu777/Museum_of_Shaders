#version 400 core

uniform float iTime;
uniform vec3 camPos;
uniform float angle;
in vec2 fragCoord;
out vec4 fragColor;

vec4 orb; 

float map(vec3 p, float s)
{
	float scale = 1;
	orb = vec4(100.0); 
	
	for (int i = 0; i < 8; i++)
	{
		p = -1.0 + 2.0 * fract(0.5 * p + 0.5);
		float r2 = dot(p, p);
        orb = min(orb, vec4(abs(p), r2));
		
		float k = s / r2;
		p *= k;
		scale *= k;
	}
	return 0.25 * (abs(p.x) + abs(p.y)) / scale;
}

float trace( in vec3 ro, in vec3 rd, float s )
{
	float maxd = 30.0;
    float t = 0.01;
    for (int i = 0; i < 150; i++)
    {
	    float precis = 0.001 * t;
        
	    float h = map(ro + rd * t, s);
        if (h < precis || t > maxd)
            break;
        t += h;
    }
    if (t > maxd)
        t = -1.0;
    return t;
}

vec3 calcNormal( in vec3 pos, in float t, in float s )
{
    float precis = 0.001 * t;

    vec2 e = vec2(1.0,-1.0) * precis;
    return normalize(e.xyy * map(pos + e.xyy, s) + 
					 e.yyx * map(pos + e.yyx, s) + 
					 e.yxy * map(pos + e.yxy, s) + 
                     e.xxx * map(pos + e.xxx, s));
}

vec3 render( in vec3 ro, in vec3 rd, in float anim )
{
    vec3 col = vec3(0.0);
    float t = trace(ro, rd, anim);
    if (t > 0.0)
    {
        vec4 tra = orb;
        vec3 pos = ro + t * rd;
        vec3 nor = calcNormal(pos, t, anim);
        vec3  light = vec3(0.5, 0.5, 0.5);
        float key = clamp(dot(light, nor), 0.0, 1.0);
        vec3 brdf = vec3(0.30, 0.20, 0.10) + vec3(1.00, 0.40, 0.00) * key;
        vec3 rgb = vec3(1.0);
        rgb = mix(rgb, vec3(0.90, 0.20, 0.20), clamp(10.0 * tra.y, 0.0, 1.0));
        col = rgb * brdf * exp(-0.2 * t);
    }
    return sqrt(col);
}

void main()
{
    float anim = (sin(iTime * 0.2) + 1) * 0.6;
    vec3 tot = vec3(0.0);
    vec2 uv = 2.0 * fragCoord - 1.0f;
    vec3 ro;
    ro = camPos + vec3(1.0, 5.0, 5.0);
    mat2 camRot = mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
    vec3 tmp = vec3(uv, 1.0);
    tmp.xz = camRot * tmp.xz;
    vec3 rd = -normalize(tmp);
    tot += render(ro, rd, anim);
	fragColor = vec4(tot, 1.0);
}
