#version 130

in vec3 pass_Color;
in vec2 pass_Unwrap;
in float pass_SpriteIndex; // it crashes when using int or uint - wtf?

//uniform sampler2D tex;
uniform sampler2DArray atlas;

out vec4 out_Color;

void main()
{
    //out_Color = texture(tex, pass_Unwrap) * vec4(pass_Color, 1.0f);
    //out_Color = texture(atlas, vec3(pass_Unwrap, pass_SpriteIndex)) * vec4(pass_Color, 1.0f);
    out_Color = texture(atlas, vec3(pass_Unwrap, pass_SpriteIndex)) * vec4(pass_Color, 1.0f);
}
