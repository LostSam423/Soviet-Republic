#version 330

layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 aCol;
layout ( location = 2) in vec2 aTex;

out vec3 aColor;
out vec2 Texcoord;

void main ()
{
  gl_Position = vec4 (vp, 1.0);
  aColor = aCol;
  Texcoord = aTex;
}
