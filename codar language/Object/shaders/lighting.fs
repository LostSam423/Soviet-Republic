# version 330

out vec4 Fragcolor;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    Fragcolor = vec4(objectColor * lightColor, 1.0);
}
