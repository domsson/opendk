#version 140

in vec3 in_Position;
//in vec3 in_Color;
in vec2 in_Unwrap;
//in vec3 in_Normal;

uniform isamplerBuffer cubes;
uniform samplerBuffer light;
uniform isamplerBuffer visibility;
uniform isamplerBuffer columns;
uniform mat4 columnInfo;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 pass_Color;
out vec2 pass_Unwrap;
flat out int pass_Sprite; // `flat` for 'no interpolation'

/*
vec3 VERTEX_ID_TO_CUBE_SIDE[8] = vec3[](
	vec3( 0.0, 0.0, 0.0 ),
	vec3( 0.5, 0.5, 0.5 )
);
*/

int VERTEX_ID_TO_CUBE_SIDE[6] = int[](
	4, // TOP
	5, // BOTTOM
	2, // FRONT
	1, // RIGHT
	0, // BACK
	3  // LEFT
);

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

ivec4 LIGHT_LEVEL_LOOKUPS[24] = ivec4[](
	ivec4(7, 3, 6, 1), //  0 (TOP - front left)
	ivec4(7, 5, 8, 1), //  1 (TOP - front right)
	ivec4(5, 1, 2, 1), //  2 (TOP - back right)
	ivec4(3, 1, 0, 1), //  3 (TOP - back left)
	ivec4(1, 3, 0, 1), //  4 (BOTTOM - back left)
	ivec4(5, 1, 2, 1), //  5 (BOTTOM - back right)
	ivec4(7, 5, 8, 1), //  6 (BOTTOM - front right)
	ivec4(3, 7, 6, 1), //  7 (BOTTOM - front left)
	ivec4(3, 6, 7, 0), //  8 (FRONT - left)
	ivec4(5, 7, 8, 0), //  9 (FRONT - right)
	ivec4(5, 7, 8, 0), // 10 (FRONT - right)
	ivec4(3, 6, 7, 0), // 11 (FRONT - left)
	ivec4(5, 7, 8, 0), // 12 (RIGHT - left)
	ivec4(5, 1, 2, 0), // 13 (RIGHT - right)
	ivec4(5, 1, 2, 0), // 14 (RIGHT - right)
	ivec4(5, 7, 8, 0), // 15 (RIGHT - left)
	ivec4(1, 5, 2, 0), // 16 (BACK  - left)
	ivec4(1, 3, 0, 0), // 17 (BACK  - right)
	ivec4(1, 3, 0, 0), // 18 (BACK  - right)
	ivec4(1, 5, 2, 0), // 19 (BACK  - left)
	ivec4(3, 1, 0, 0), // 20 (LEFT  - left)
	ivec4(3, 7, 6, 0), // 21 (LEFT  - right)
	ivec4(3, 7, 6, 0), // 22 (LEFT  - right)
	ivec4(3, 1, 0, 0)  // 23 (LEFT  - left)
);

int getSpriteFromTexBuffer(int cube)
{
	int cubeSide = VERTEX_ID_TO_CUBE_SIDE[int(gl_VertexID / 4)];
	return texelFetch(cubes, cube * 6 + cubeSide).r;
}

/*
float getLightLevelFromBuffer(int x, int z)
{
	int texels[9] = int[](
		(z - 1) * 255 + (x - 1), // 0
		(z - 1) * 255 + (x + 0), // 1
		(z - 1) * 255 + (x + 1), // 2
		(z + 0) * 255 + (x - 1), // 3
		(z + 0) * 255 + (x + 0), // 4
		(z + 0) * 255 + (x + 1), // 5
		(z + 1) * 255 + (x - 1), // 6
		(z + 1) * 255 + (x + 0), // 7
		(z + 1) * 255 + (x + 1)  // 8
	);

	float f = texelFetch(light, texels[LIGHT_LEVEL_LOOKUPS[gl_VertexID][0]]).r;
	float s = texelFetch(light, texels[LIGHT_LEVEL_LOOKUPS[gl_VertexID][1]]).r;
	float d = texelFetch(light, texels[LIGHT_LEVEL_LOOKUPS[gl_VertexID][2]]).r;
	float c = LIGHT_LEVEL_LOOKUPS[gl_VertexID][3] * texelFetch(light, texels[4]).r;
	float p = 3.0f + LIGHT_LEVEL_LOOKUPS[gl_VertexID][3];

	return (c + f + s + d) / p;
}
*/

float getLightLevelFromBuffer(int x, int z)
{
	float c = 0.0f; // current subtile (center)
	float f = 0.0f; // subtile in front of current
	float s = 0.0f; // subtile to side of current
	float d = 0.0f; // subtile diagonal to current
	float p = 0.333333f; // multiply the sum by this at the end

	switch (gl_VertexID)
	{
		case  0:	// TOP - front left
			f = texelFetch(light, (z + 1) * 255 + (x + 0)).r; // 7
			s = texelFetch(light, (z + 0) * 255 + (x - 1)).r; // 3
			d = texelFetch(light, (z + 1) * 255 + (x - 1)).r; // 6
			c = texelFetch(light, z * 255 + x).r;
			p = 0.25;
			break;
		case  1:	// TOP - front right
			f = texelFetch(light, (z + 1) * 255 + (x + 0)).r; // 7
			s = texelFetch(light, (z + 0) * 255 + (x + 1)).r; // 5
			d = texelFetch(light, (z + 1) * 255 + (x + 1)).r; // 8
			c = texelFetch(light, z * 255 + x).r;
			p = 0.25;
			break;
		case  2:	// TOP - back right
			f = texelFetch(light, (z + 0) * 255 + (x + 1)).r; // 5
			s = texelFetch(light, (z - 1) * 255 + (x + 0)).r; // 1
			d = texelFetch(light, (z - 1) * 255 + (x + 1)).r; // 2
			c = texelFetch(light, z * 255 + x).r;
			p = 0.25;
			break;
		case  3:	// TOP - back left
			f = texelFetch(light, (z + 0) * 255 + (x - 1)).r; // 3
			s = texelFetch(light, (z - 1) * 255 + (x + 0)).r; // 1
			d = texelFetch(light, (z - 1) * 255 + (x - 1)).r; // 0
			c = texelFetch(light, z * 255 + x).r;
			p = 0.25;
			break;
		case  4:	// BOTTOM - back left
			f = texelFetch(light, (z - 1) * 255 + (x + 0)).r; // 1
			s = texelFetch(light, (z + 0) * 255 + (x - 1)).r; // 3
			d = texelFetch(light, (z - 1) * 255 + (x - 1)).r; // 0
			c = texelFetch(light, z * 255 + x).r;
			p = 0.25;
			break;
		case  5:	// BOTTOM - back right
			f = texelFetch(light, (z + 0) * 255 + (x + 1)).r; // 5
			s = texelFetch(light, (z - 1) * 255 + (x + 0)).r; // 1
			d = texelFetch(light, (z - 1) * 255 + (x + 1)).r; // 2
			c = texelFetch(light, z * 255 + x).r;
			p = 0.25;
			break;
		case  6:	// BOTTOM - front right
			f = texelFetch(light, (z + 1) * 255 + (x + 0)).r; // 7
			s = texelFetch(light, (z + 0) * 255 + (x + 1)).r; // 5
			d = texelFetch(light, (z + 1) * 255 + (x + 1)).r; // 8
			c = texelFetch(light, z * 255 + x).r;
			p = 0.25;
			break;
		case  7:	// BOTTOM - front left
			f = texelFetch(light, (z + 0) * 255 + (x - 1)).r; // 3
			s = texelFetch(light, (z + 1) * 255 + (x + 0)).r; // 7
			d = texelFetch(light, (z + 1) * 255 + (x - 1)).r; // 6
			c = texelFetch(light, z * 255 + x).r;
			p = 0.25;
			break;
		case  8:	// FRONT - left
		case 11:
			// TODO check if these are fsd
			f = texelFetch(light, (z + 0) * 255 + (x - 1)).r;
			s = texelFetch(light, (z + 1) * 255 + (x - 1)).r;
			d = texelFetch(light, (z + 1) * 255 + (x + 0)).r;
			c = 0.0f;
			p = 0.333333f;
			break;
		case  9:	// FRONT - right
		case 10:
			// TODO check if these are fsd
			f = texelFetch(light, (z + 0) * 255 + (x + 1)).r;
			s = texelFetch(light, (z + 1) * 255 + (x + 0)).r;
			d = texelFetch(light, (z + 1) * 255 + (x + 1)).r;
			c = 0.0f;
			p = 0.333333f;
			break;
		case 12:	// RIGHT - left
		case 15:
			// TODO check if these are fsd
			f = texelFetch(light, (z + 0) * 255 + (x + 1)).r;
			s = texelFetch(light, (z + 1) * 255 + (x + 0)).r;
			d = texelFetch(light, (z + 1) * 255 + (x + 1)).r;
			c = 0.0f;
			p = 0.333333f;
			break;
		case 13:	// RIGHT - right
		case 14:
			// TODO check if these are fsd
			f = texelFetch(light, (z + 0) * 255 + (x + 1)).r;
			s = texelFetch(light, (z - 1) * 255 + (x + 0)).r;
			d = texelFetch(light, (z - 1) * 255 + (x + 1)).r;
			c = 0.0f;
			p = 0.333333f;
			break;
		case 16:	// BACK - left
		case 19:
			f = texelFetch(light, (z - 1) * 255 + (x + 0)).r;
			s = texelFetch(light, (z + 0) * 255 + (x + 1)).r;
			d = texelFetch(light, (z - 1) * 255 + (x + 1)).r;
			c = 0.0f;
			p = 0.333333f;
			break;
		case 17:	// BACK - right
		case 18:
			f = texelFetch(light, (z - 1) * 255 + (x + 0)).r;
			s = texelFetch(light, (z + 0) * 255 + (x - 1)).r;
			d = texelFetch(light, (z - 1) * 255 + (x - 1)).r;
			c = 0.0f;
			p = 0.333333f;
			break;
		case 20:	// LEFT - left
		case 23:
			f = texelFetch(light, (z + 0) * 255 + (x - 1)).r;
			s = texelFetch(light, (z - 1) * 255 + (x + 0)).r;
			d = texelFetch(light, (z - 1) * 255 + (x - 1)).r;
			c = 0.0f;
			p = 0.333333f;
			break;
		case 21:	// LEFT - right
		case 22:
			f = texelFetch(light, (z + 0) * 255 + (x - 1)).r;
			s = texelFetch(light, (z + 1) * 255 + (x + 0)).r;
			d = texelFetch(light, (z + 1) * 255 + (x - 1)).r;
			c = 0.0f;
			p = 0.333333f;
			break;

	}
	return (c + f + s + d) * p;
}

/*
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
*/

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
	//skewedPos.y += rand(pos.xzy) * 0.10;
	return skewedPos;
}

int getCubeIndexFromInstanceID()
{
	return gl_InstanceID - int(gl_InstanceID / 9) * 9;
}

int getCubeFromColumnBuffer(int column)
{
	int cube = getCubeIndexFromInstanceID();
	return texelFetch(columns, (column * 9) + cube).r;
}

int getBaseSpriteFromColumnBuffer(int column)
{
	return texelFetch(columns, column * 9).r;
}

int getColumnFromInstanceID()
{
	/*
	if (gl_InstanceID < 9)  { return int(columnInfo[0][0]); }
	if (gl_InstanceID < 18) { return int(columnInfo[0][1]); }
	if (gl_InstanceID < 27) { return int(columnInfo[0][2]); }
	if (gl_InstanceID < 36) { return int(columnInfo[1][0]); }
	if (gl_InstanceID < 45) { return int(columnInfo[1][1]); }
	if (gl_InstanceID < 54) { return int(columnInfo[1][2]); }
	if (gl_InstanceID < 63) { return int(columnInfo[2][0]); }
	if (gl_InstanceID < 72) { return int(columnInfo[2][1]); }
	if (gl_InstanceID < 81) { return int(columnInfo[2][2]); }
	*/
	return int(columnInfo[int(gl_InstanceID / 27)][(gl_InstanceID / 9) % 3]);
}

vec2 getColumnPositionFromInstanceID()
{
	/*
	int column = int(gl_InstanceID / 9);
	if (column == 0) { return vec2(0.0f, 0.0f); }
	if (column == 1) { return vec2(0.0f, 1.0f); }
	if (column == 2) { return vec2(0.0f, 2.0f); }
	if (column == 3) { return vec2(1.0f, 0.0f); }
	if (column == 4) { return vec2(1.0f, 1.0f); }
	if (column == 5) { return vec2(1.0f, 2.0f); }
	if (column == 6) { return vec2(2.0f, 0.0f); }
	if (column == 7) { return vec2(2.0f, 1.0f); }
	if (column == 8) { return vec2(2.0f, 2.0f); }
	*/
	return vec2(int(gl_InstanceID / 27), (gl_InstanceID / 9) % 3);
}

int getVisibilityFromBuffer(int x, int z)
{
	int slab = (z/3) * 85 + (x/3);
	return texelFetch(visibility, slab).r;
}

void main()
{
	// Sprite (Which texture to use)
	int column = getColumnFromInstanceID();
	int sprite = getCubeIndexFromInstanceID()==0 ? getBaseSpriteFromColumnBuffer(column) : getSpriteFromTexBuffer(getCubeFromColumnBuffer(column));

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


	// Position (Geometry)
	vec4 cubePos = vec4(
		columnInfo[3][0] + getColumnPositionFromInstanceID().x,
		columnInfo[3][1] + getCubeIndexFromInstanceID(),
		columnInfo[3][2] + getColumnPositionFromInstanceID().y,
		1.0f
	);

	gl_Position = projectionMatrix * viewMatrix * skewPosition(cubePos + vec4(in_Position, 1.0f));

	// Color (Light level)
	float lightLevel = getLightLevelFromBuffer(int(cubePos.x), int(cubePos.z));
	//float lightLevel = 0.7f;
	/*
	if (getVisibilityFromBuffer(int(cubePos.x), int(cubePos.z)) == 0)
	{
		lightLevel = 0.0f;
	}
	*/
	pass_Color = vec3(1.0 * lightLevel, 1.0 * lightLevel, 1.0 * lightLevel);
	//pass_Color = vec3(lightLevel, lightLevel, lightLevel);

	// Unwrap (Texture coordinates)
	pass_Unwrap = in_Unwrap;


}
