#version 330
uniform vec4 OurColor;
out vec4 frag_colour;

void main () 
{
  frag_colour = OurColor;
}
