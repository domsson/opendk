#version 130

in vec3 in_Position;
in vec3 in_Color;
in vec2 in_Unwrap;

uniform ivec2 sprites;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 pass_Color;
out vec2 pass_Unwrap;
out float pass_Sprite;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0f);
    pass_Color = in_Color;

	pass_Unwrap = in_Unwrap;
	pass_Sprite = gl_VertexID < 8 ? sprites[0] : sprites[1];
}
