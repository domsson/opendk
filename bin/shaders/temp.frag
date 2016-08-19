#version 130

in vec3 pass_Color;
in vec2 pass_Unwrap;

out vec4 out_Color;

//uniform sampler2D tex;
uniform sampler2DArray atlas;

void main()
{
    //out_Color = texture(tex, pass_Unwrap) * vec4(pass_Color, 1.0f);
    out_Color = texture(atlas, vec3(pass_Unwrap, 1)) * vec4(pass_Color, 1.0f);
}
