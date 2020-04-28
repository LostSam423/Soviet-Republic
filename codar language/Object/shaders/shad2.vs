#version 330

layout(location = 0 ) in vec3 aPos;
layout (location = 1) in vec2 aTex;

out vec3 aColor;
out vec2 Texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection*view*model*vec4(aPos, 1.0);
    aColor = vec3(0.0f, 0.2f, 0.3f);
    Texcoord = aTex;
}
