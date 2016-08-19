#version 130

in vec3 in_Position;
in vec3 in_Color;
in vec2 in_Unwrap;

uniform vec4 uvOffsets;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 pass_Color;
out vec2 pass_Unwrap;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0f);
    pass_Color = in_Color;

	//pass_Unwrap.x = (in_Unwrap.x == 0.0f) ? uvOffsets[0] : uvOffsets[2];
	//pass_Unwrap.y = (in_Unwrap.y == 0.0f) ? uvOffsets[1] : uvOffsets[3];

	pass_Unwrap = in_Unwrap;
}
