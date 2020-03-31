
#version 330

in vec3 aColor;
in vec2 Texcoord;

out vec4 frag_colour;

uniform sampler2D ourTexture;

void main ()
{
  frag_colour = vec4(aColor,0.0 );
}
