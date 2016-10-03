#version 140

in vec3 pass_Color;
in vec2 pass_Unwrap;
flat in int pass_Sprite;

uniform sampler2DArray atlas;

out vec4 out_Color;

vec4 adjustContrast(vec4 color, float contrast)
{
	 return vec4(((color.rgb - 0.5f) * max(contrast, 0)) + 0.5f, 1.0f);
}

void main()
{
	if (pass_Sprite == 0)
	{
		discard;
	}
    //out_Color = texture(atlas, vec3(pass_Unwrap, pass_Sprite)) * (vec4(pass_Color, 1.0f) + vec4(0.3f, 0.3f, 0.3f, 1.0f));
    out_Color = adjustContrast(texture(atlas, vec3(pass_Unwrap, pass_Sprite)) * (vec4(pass_Color, 1.0f)), 1.05f);

}
