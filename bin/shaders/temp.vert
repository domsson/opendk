#version 130

in vec3 position;
in vec3 color;
in vec2 texCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    //gl_Position = vec4(position, 1.0f);
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0f);
    ourColor = color;
    TexCoord = texCoord;
}
