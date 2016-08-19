#version 130

in vec3 pass_Color;
in vec2 pass_Unwrap;
in float pass_Sprite; // it crashes when using int or uint - wtf?

uniform sampler2DArray atlas;

out vec4 out_Color;

void main()
{
    out_Color = texture(atlas, vec3(pass_Unwrap, pass_Sprite)) * vec4(pass_Color, 1.0f);
}
