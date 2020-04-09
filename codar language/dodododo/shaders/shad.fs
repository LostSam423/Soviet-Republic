
#version 330

in vec3 aColor;
in vec2 Texcoord;

out vec4 frag_colour;

uniform sampler2D txt1;
uniform sampler2D txt2;
uniform float change;
void main ()
{
  frag_colour = mix(texture(txt1, Texcoord), texture(txt2, Texcoord), change);
}
