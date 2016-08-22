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

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0f);
    pass_Color = in_Color;

	pass_Unwrap = in_Unwrap;
	//pass_Sprite = gl_VertexID < 8 ? sprites[0] : sprites[1];
	pass_Sprite = getSprite();
}
