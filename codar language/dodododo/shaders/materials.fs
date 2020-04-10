# version 330

out vec4 Fragcolor;

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
};

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

in vec3 Normal;
in vec3 FragPos;
void main()
{

    vec3 ambient = material.ambient * light.ambient;
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = (diff * material.diffuse) * light.diffuse;
    
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect( -lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = (spec * material.specular) * light.specular;
    
    vec3 result = ambient+ diffuse + specular;
    Fragcolor = vec4(result, 1.0);
}