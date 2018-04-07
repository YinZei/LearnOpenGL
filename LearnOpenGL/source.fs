#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float     shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec2 texCoord;
in vec3 norm;
in vec3 fragPos;

uniform Material material;
uniform Light light;
uniform vec3 cameraPos;

void main()
{
	//环境光
	vec3 ambient = light.ambient * texture(material.diffuse, texCoord).rgb;
	//vec3 ambient = vec3(1.0f, 1.0f, 1.0f);
  	
    // 漫反射 
    vec3 norm = normalize(norm);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, texCoord).rgb;  
    
    // 镜面光
	vec3 specular;
	if (dot(norm, lightDir) <= 0.0f)
	{
		specular = vec3(0.0f, 0.0f, 0.0f);
	}
	else
	{
		vec3 viewDir = normalize(cameraPos - fragPos);
		vec3 reflectDir = reflect(-lightDir, norm);  
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		specular = light.specular * spec * texture(material.specular, texCoord).rgb;  
	}
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}