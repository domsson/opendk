#version 130

in vec3 pass_Color;
in vec2 pass_Unwrap;

out vec4 out_Color;

uniform sampler2D tex;

void main()
{
    out_Color = texture(tex, pass_Unwrap) * vec4(pass_Color, 1.0f);
}
