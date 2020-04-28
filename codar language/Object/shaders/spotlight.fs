# version 330

out vec4 Fragcolor;

struct Material{
    
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
    
};

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

in vec3 Normal;
in vec3 FragPos;
in vec2 Texcoords;

void main()
{
    vec3 lightDir = normalize(light.position - FragPos);
    
    
    
    vec3 ambient = vec3(texture(material.diffuse,Texcoords)) * light.ambient;
    
    vec3 norm = normalize(Normal);
    
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(texture(material.diffuse,Texcoords)) * light.diffuse;
    
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect( -lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spec * vec3(texture(material.specular,Texcoords)) * light.specular;
    
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - epsilon), 0.0, 1.0);
    diffuse *= intensity;
    specular *= intensity;
    
    float distance = length(light.position - FragPos);
    float attenuation = 1.0/(light.constant + light.linear* distance + light.quadratic*distance * distance);
    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    vec3 result = ambient+ diffuse + specular;
    Fragcolor = vec4(result, 1.0);
    
}
