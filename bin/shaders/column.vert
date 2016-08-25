#version 140

in vec3 in_Position;
in vec3 in_Color;
in vec2 in_Unwrap;

uniform isamplerBuffer cubes;
uniform mat4 columnInfo;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 pass_Color;
out vec2 pass_Unwrap;
flat out int pass_Sprite; // `flat` for 'no interpolation'

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

int getSpriteFromTexBuffer(int cube)
{
	if (gl_VertexID < 4)
	{
		// TOP
		return texelFetch(cubes, cube * 6 + 4).r;
	}
	if (gl_VertexID < 8)
	{
		// BOTTOM
		return texelFetch(cubes, cube * 6 + 5).r;
	}
	if (gl_VertexID < 12)
	{
		// FRONT
		return texelFetch(cubes, cube * 6 + 2).r;
	}
	if (gl_VertexID < 16)
	{
		// RIGHT
		return texelFetch(cubes, cube * 6 + 1).r;
	}
	if (gl_VertexID < 20)
	{
		// BACK
		return texelFetch(cubes, cube * 6 + 0).r;
	}
	if (gl_VertexID < 24)
	{
		// LEFT
		return texelFetch(cubes, cube * 6 + 3).r;
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
	pos += 1.5f;
	skewedPos.x += rand(pos.xyz) * 0.275;
	//skewedPos.y += rand(pos.xzy) * 0.10;
	skewedPos.z += rand(pos.zyx) * 0.275;
	return skewedPos;
}

int getCubeFromInstanceID()
{
	switch (gl_InstanceID)
	{
		case 0:	// base block
		return int(columnInfo[0][0]);
		case 1: // height 0
		return int(columnInfo[0][1]);
		case 2: // height 1
		return int(columnInfo[0][2]);
		case 3: // height 2
		return int(columnInfo[1][0]);
		case 4: // height 3
		return int(columnInfo[1][1]);
		case 5: // height 4
		return int(columnInfo[1][2]);
		case 6: // height 5
		return int(columnInfo[2][0]);
		case 7: // height 6
		return int(columnInfo[2][1]);
		case 8: // height 7
		return int(columnInfo[2][2]);
	}
}

void main()
{
    //gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0f);

    vec4 columnPos = vec4(columnInfo[3][0], columnInfo[3][1] + float(gl_InstanceID), columnInfo[3][2], 1.0f);

    //gl_Position = projectionMatrix * viewMatrix * skewPosition(modelMatrix * vec4(in_Position, 1.0f));
    gl_Position = projectionMatrix * viewMatrix * skewPosition(columnPos + vec4(in_Position, 1.0f));
    pass_Color = in_Color;

	pass_Unwrap = in_Unwrap;
	pass_Sprite = getSpriteFromTexBuffer(getCubeFromInstanceID());
}
