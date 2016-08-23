#version 130

in vec3 in_Position;
in vec3 in_Color;
in vec2 in_Unwrap;

uniform ivec2 sprites;
uniform int sides[6];

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 pass_Color;
out vec2 pass_Unwrap;
out float pass_Sprite;

float getSprite() {
	if (gl_VertexID < 4)
	{
		return sides[0];
	}
	if (gl_VertexID < 8)
	{
		return sides[1];
	}
	if (gl_VertexID < 12)
	{
		return sides[2];
	}
	if (gl_VertexID < 16)
	{
		return sides[3];
	}
	if (gl_VertexID < 20)
	{
		return sides[4];
	}
	if (gl_VertexID < 24)
	{
		return sides[5];
	}
}

// http://stackoverflow.com/questions/12964279/whats-the-origin-of-this-glsl-rand-one-liner
float rand(vec2 co){
	return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

// http://byteblacksmith.com/improvements-to-the-canonical-one-liner-glsl-rand-for-opengl-es-2-0/
// Modified so it works on a vec3 instead vec2 - jd
float rand(vec3 co){
	//return fract(sin(dot(co.xyz ,vec3(12.9898, 78.233, 22.721))) * 43758.5453);

    highp float a = 12.9898;
    highp float b = 78.233;
    highp float c = 22.721;
    highp float d = 43758.5453;
    highp float dt= dot(co.xyz ,vec3(a,b,c));
    highp float sn= mod(dt,3.14);
    return fract(sin(sn) * d);
}

vec4 skewPosition(vec4 pos)
{
	vec4 skewedPos = pos;
	//vec4 posPlus = vec4(pos.x + 1.0f, pos.y + 1.0f, pos.z + 1.0f, pos.w);
	pos += 1.5f;
	skewedPos.x += rand(pos.xyz) * 0.275;
	//skewedPos.y += rand(pos.xzy) * 0.10;
	skewedPos.z += rand(pos.zyx) * 0.275;
	return skewedPos;
}

void main()
{
    //gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0f);
    gl_Position = projectionMatrix * viewMatrix * skewPosition(modelMatrix * vec4(in_Position, 1.0f));
    pass_Color = in_Color;

	pass_Unwrap = in_Unwrap;
	//pass_Sprite = gl_VertexID < 8 ? sprites[0] : sprites[1];
	pass_Sprite = getSprite();
}
