#version 140

in vec3 in_Position;
in vec3 in_Color;
in vec2 in_Unwrap;
in vec3 in_Normal;

uniform isamplerBuffer cubes;
uniform samplerBuffer light;
uniform isamplerBuffer visibility;
uniform mat4 columnInfo;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewProjectionMatrix;

out vec3 pass_Color;
out vec2 pass_Unwrap;
flat out int pass_Sprite; // `flat` for 'no interpolation'

/*
	// CUBE.DAT face order:
	CUBE_BACK   = 0,
	CUBE_RIGHT  = 1,
	CUBE_FRONT  = 2,
	CUBE_LEFT   = 3,
	CUBE_TOP    = 4,
	CUBE_BOTTOM = 5

	// CubeGeometry face order:
	TOP
	BOTTOM
	FRONT
	RIGHT
	BACK
	LEFT
*/

int getSpriteFromTexBuffer(int cube)
{
	if (gl_VertexID < 4)	// TOP
	{
		return texelFetch(cubes, cube * 6 + 4).r;
	}
	if (gl_VertexID < 8)	// BOTTOM
	{
		return texelFetch(cubes, cube * 6 + 5).r;
	}
	if (gl_VertexID < 12)	// FRONT
	{
		return texelFetch(cubes, cube * 6 + 2).r;
	}
	if (gl_VertexID < 16)	// RIGHT
	{
		return texelFetch(cubes, cube * 6 + 1).r;
	}
	if (gl_VertexID < 20)	// BACK
	{
		return texelFetch(cubes, cube * 6 + 0).r;
	}
	if (gl_VertexID < 24)	// LEFT
	{
		return texelFetch(cubes, cube * 6 + 3).r;
	}
}

vec3 getLightLevelFromColumnData()
{
	if (gl_VertexID < 4)	// TOP - needs special treatment
	{
		if (gl_VertexID == 0) // TOP - FRONT-LEFT
		{
			float intensity = (columnInfo[0][3] + columnInfo[3][3]) * 0.5f;
			return vec3(intensity, intensity, intensity);
		}
		if (gl_VertexID == 1) // TOP - FRONT-RIGHT
		{
			float intensity = (columnInfo[0][3] + columnInfo[1][3]) * 0.5f;
			return vec3(intensity, intensity, intensity);
		}
		if (gl_VertexID == 2) // TOP - BACK-RIGHT
		{
			float intensity = (columnInfo[2][3] + columnInfo[1][3]) * 0.5f;
			return vec3(intensity, intensity, intensity);
		}
		if (gl_VertexID == 3) // TOP - BACK-LEFT
		{
			float intensity = (columnInfo[2][3] + columnInfo[3][3]) * 0.5f;
			return vec3(intensity, intensity, intensity);
		}
	}
	if (gl_VertexID < 8)	// BOTTOM - needs special treatment
	{
		return vec3(1.0f, 1.0f, 1.0f); // TODO
	}
	if (gl_VertexID < 12)	// FRONT
	{
		return vec3(columnInfo[0][3], columnInfo[0][3], columnInfo[0][3]);
	}
	if (gl_VertexID < 16)	// RIGHT
	{
		return vec3(columnInfo[1][3], columnInfo[1][3], columnInfo[1][3]);
	}
	if (gl_VertexID < 20)	// BACK
	{
		return vec3(columnInfo[2][3], columnInfo[2][3], columnInfo[2][3]);
	}
	if (gl_VertexID < 24)	// LEFT
	{
		return vec3(columnInfo[3][3], columnInfo[3][3], columnInfo[3][3]);
	}
}

float getLightLevelFromBuffer(int x, int z)
{
	//float c = -0.3f; // current subtile (center)
	float c = 0.0f; // current subtile (center)
	float f = 0.0f; // subtile in front of current
	float s = 0.0f; // subtile to side of current
	float d = 0.0f; // subtile diagonal to current
	float p = 0.333333f; // multiply the sum by this at the end

	if (gl_VertexID < 8) // TOP OR BOTTOM
	{
		c = texelFetch(light, z * 255 + x).r;
		p = 0.25;
	}

	if (gl_VertexID == 0)	// TOP - front left
	{
		f = texelFetch(light, (z + 1) * 255 + (x + 0)).r;
		s = texelFetch(light, (z + 0) * 255 + (x - 1)).r;
		d = texelFetch(light, (z + 1) * 255 + (x - 1)).r;
	}
	if (gl_VertexID == 1)	// TOP - front right
	{
		f = texelFetch(light, (z + 1) * 255 + (x + 0)).r;
		s = texelFetch(light, (z + 0) * 255 + (x + 1)).r;
		d = texelFetch(light, (z + 1) * 255 + (x + 1)).r;
	}
	if (gl_VertexID == 2)	// TOP - back right
	{
		f = texelFetch(light, (z + 0) * 255 + (x + 1)).r;
		s = texelFetch(light, (z - 1) * 255 + (x + 0)).r;
		d = texelFetch(light, (z - 1) * 255 + (x + 1)).r;
	}
	if (gl_VertexID == 3)	// TOP - back left
	{
		f = texelFetch(light, (z + 0) * 255 + (x - 1)).r;
		s = texelFetch(light, (z - 1) * 255 + (x + 0)).r;
		d = texelFetch(light, (z - 1) * 255 + (x - 1)).r;
	}

	if (gl_VertexID == 4)	// BOTTOM - back left
	{
		f = texelFetch(light, (z - 1) * 255 + (x + 0)).r;
		s = texelFetch(light, (z + 0) * 255 + (x - 1)).r;
		d = texelFetch(light, (z - 1) * 255 + (x - 1)).r;
	}
	if (gl_VertexID == 5)	// BOTTOM - back right
	{
		f = texelFetch(light, (z + 0) * 255 + (x + 1)).r;
		s = texelFetch(light, (z - 1) * 255 + (x + 0)).r;
		d = texelFetch(light, (z - 1) * 255 + (x + 1)).r;
	}
	if (gl_VertexID == 6)	// BOTTOM - front right
	{
		f = texelFetch(light, (z + 1) * 255 + (x + 0)).r;
		s = texelFetch(light, (z + 0) * 255 + (x + 1)).r;
		d = texelFetch(light, (z + 1) * 255 + (x + 1)).r;
	}
	if (gl_VertexID == 7)	// BOTTOM - front left
	{
		f = texelFetch(light, (z + 0) * 255 + (x - 1)).r;
		s = texelFetch(light, (z + 1) * 255 + (x + 0)).r;
		d = texelFetch(light, (z + 1) * 255 + (x - 1)).r;
	}

	if (gl_VertexID == 8 || gl_VertexID == 11)	// FRONT - left
	{
		// TODO check if these are fsd
		f = texelFetch(light, (z + 0) * 255 + (x - 1)).r;
		s = texelFetch(light, (z + 1) * 255 + (x - 1)).r;
		d = texelFetch(light, (z + 1) * 255 + (x + 0)).r;
	}
	if (gl_VertexID == 9 || gl_VertexID == 10)	// FRONT - right
	{
		// TODO check if these are fsd
		f = texelFetch(light, (z + 0) * 255 + (x + 1)).r;
		s = texelFetch(light, (z + 1) * 255 + (x + 0)).r;
		d = texelFetch(light, (z + 1) * 255 + (x + 1)).r;
	}

	if (gl_VertexID == 12 || gl_VertexID == 15)	// RIGHT - left
	{
		// TODO check if these are fsd
		f = texelFetch(light, (z + 0) * 255 + (x + 1)).r;
		s = texelFetch(light, (z + 1) * 255 + (x + 0)).r;
		d = texelFetch(light, (z + 1) * 255 + (x + 1)).r;
	}
	if (gl_VertexID == 13 || gl_VertexID == 14)	// RIGHT - right
	{
		// TODO check if these are fsd
		f = texelFetch(light, (z + 0) * 255 + (x + 1)).r;
		s = texelFetch(light, (z - 1) * 255 + (x + 0)).r;
		d = texelFetch(light, (z - 1) * 255 + (x + 1)).r;
	}

	if (gl_VertexID == 16 || gl_VertexID == 19)	// BACK - left
	{
		f = texelFetch(light, (z - 1) * 255 + (x + 0)).r;
		s = texelFetch(light, (z + 0) * 255 + (x + 1)).r;
		d = texelFetch(light, (z - 1) * 255 + (x + 1)).r;
	}
	if (gl_VertexID == 17 || gl_VertexID == 18)	// BACK - right
	{
		f = texelFetch(light, (z - 1) * 255 + (x + 0)).r;
		s = texelFetch(light, (z + 0) * 255 + (x - 1)).r;
		d = texelFetch(light, (z - 1) * 255 + (x - 1)).r;
	}

	if (gl_VertexID == 20 || gl_VertexID == 23)	// LEFT - left
	{
		f = texelFetch(light, (z + 0) * 255 + (x - 1)).r;
		s = texelFetch(light, (z - 1) * 255 + (x + 0)).r;
		d = texelFetch(light, (z - 1) * 255 + (x - 1)).r;
	}
	if (gl_VertexID == 21 || gl_VertexID == 22)	// LEFT - right
	{
		f = texelFetch(light, (z + 0) * 255 + (x - 1)).r;
		s = texelFetch(light, (z + 1) * 255 + (x + 0)).r;
		d = texelFetch(light, (z + 1) * 255 + (x - 1)).r;
	}

	return (c + f + s + d) * p;
}

// http://stackoverflow.com/questions/12964279/whats-the-origin-of-this-glsl-rand-one-liner
float rand(vec2 co){
	return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

// http://byteblacksmith.com/improvements-to-the-canonical-one-liner-glsl-rand-for-opengl-es-2-0/
// Modified so it works on a vec3 instead vec2 - jd
float rand(vec3 co){
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
	skewedPos.z += rand(pos.zyx) * 0.275;
	return skewedPos;
}

	//skewedPos.y += rand(pos.xzy) * 0.10;

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

int getVisibilityFromBuffer(int x, int z)
{
	int slab = (z/3) * 85 + (x/3);
	return texelFetch(visibility, slab).r;
}

void main()
{
	// Position (Geometry)
    vec4 cubePos = vec4(columnInfo[3][0], columnInfo[3][1] + float(gl_InstanceID), columnInfo[3][2], 1.0f);
    gl_Position = projectionMatrix * viewMatrix * skewPosition(cubePos + vec4(in_Position, 1.0f));

	// Color (Light level)
    //pass_Color = getLightLevelFromColumnData();
    float lightLevel = getLightLevelFromBuffer(int(cubePos.x), int(cubePos.z));
	/*
    if (getVisibilityFromBuffer(int(cubePos.x), int(cubePos.z)) == 0)
    {
		lightLevel = 0.0f;
	}
	*/
	pass_Color = vec3(lightLevel, lightLevel, lightLevel);

	// Unwrap (Texture coordinates)
	pass_Unwrap = in_Unwrap;

	// Sprite (Which texture to use)
	// Base block (gl_InstanceID == 0) is directly referencing a sprite, not a cube
	int sprite = (gl_InstanceID == 0) ? getCubeFromInstanceID() : getSpriteFromTexBuffer(getCubeFromInstanceID());
	if (sprite == 544) { sprite =  40; } // dirt near water
	if (sprite == 545) { sprite =  48; } // water
	if (sprite == 546) { sprite =  56; } // lava 1
	if (sprite == 547) { sprite =  64; } // lava 2
	if (sprite == 548) { sprite =  80; } // gold 1
	if (sprite == 549) { sprite =  84; } // gold 2
	if (sprite == 550) { sprite =  88; } // gold 3
	if (sprite == 551) { sprite = 160; } // brick near water
	if (sprite == 552) { sprite =  92; } // gold near lava 1
	if (sprite == 553) { sprite =  92; } // gold near lava 1
	if (sprite == 554) { sprite =  92; } // gold near lava 1
	if (sprite == 581) { sprite = 195; } // center top of portal
	pass_Sprite = sprite;
}
