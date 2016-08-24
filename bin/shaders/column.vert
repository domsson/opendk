#version 140

in vec3 in_Position;
in vec3 in_Color;
in vec2 in_Unwrap;

//uniform ivec2 sprites;
//uniform int sides[6];

/*
layout(std140) uniform columns
{
	// up to 2048 columns with 9 cubes each
	// calc index: (column * 9) + cube
    int indices[18432];
};
*/

/*
struct Sprite
{
    int back;
    int right;
    int front;
    int left;
    int top;
    int bottom;
};

layout(std140) uniform cubes
{
	// 512 cubes with 6 sides each
	// calc index: (cube * 6) + side
	int sprites[3072];
};
*/

uniform isamplerBuffer cubesBuffer;

uniform int column; // the index of the column to draw

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 pass_Color;
out vec2 pass_Unwrap;
out float pass_Sprite;

	/*
	    // CubeSides face order:
		CUBE_BACK   = 0,
		CUBE_RIGHT  = 1,
		CUBE_FRONT  = 2,
		CUBE_LEFT   = 3,
		CUBE_TOP    = 4,
		CUBE_BOTTOM = 5

		// BlockGeometry face order:
		TOP
		BOTTOM
		FRONT
		RIGHT
		BACK
		LEFT
	*/
	/*
int getSprite() {



	if (gl_VertexID < 4)
	{
		// TOP
		//return sprites[column * 6 + 4];
		return sprites[4];
		//  0:000,  1:000,  2:002,  3:003,  4:005,  5:004,
		//  6:008,  7:005,  8:007,  9:006, 10:005, 11:009,
		// 12:009, 13:002, 14:00B, 15:00C, 16:005, 17:00D,
		// AH! GOT IT! IT GOES TO EVERY 4th VALUE! WHY???

		//  0:000,  1:003,  2:004,  3:005,  4:006
		// Okay.. so with the struct, it jumps to every
		// 8th value... WTF DUDE
	}
	if (gl_VertexID < 8)
	{
		// BOTTOM
		return sprites[6];
	}
	if (gl_VertexID < 12)
	{
		// FRONT
		return sprites[6];
	}
	if (gl_VertexID < 16)
	{
		// RIGHT
		return sprites[6];
	}
	if (gl_VertexID < 20)
	{
		// BACK
		return sprites[6];
	}
	if (gl_VertexID < 24)
	{
		// LEFT
		return sprites[6];
	}
}
*/

int getSpriteFromTexBuffer()
{
	if (gl_VertexID < 4)
	{
		// TOP
		return texelFetch(cubesBuffer, column * 6 + 4).r;
	}
	if (gl_VertexID < 8)
	{
		// BOTTOM
		return texelFetch(cubesBuffer, column * 6 + 5).r;
	}
	if (gl_VertexID < 12)
	{
		// FRONT
		return texelFetch(cubesBuffer, column * 6 + 2).r;
	}
	if (gl_VertexID < 16)
	{
		// RIGHT
		return texelFetch(cubesBuffer, column * 6 + 1).r;
	}
	if (gl_VertexID < 20)
	{
		// BACK
		return texelFetch(cubesBuffer, column * 6 + 0).r;
	}
	if (gl_VertexID < 24)
	{
		// LEFT
		return texelFetch(cubesBuffer, column * 6 + 3).r;
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
	//pass_Sprite = getSprite();
	pass_Sprite = getSpriteFromTexBuffer();
}
