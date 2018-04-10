#version 330 core
struct Material {
    sampler2D diffuse0;
    sampler2D specular0;
    float     shininess;
};

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	float constant;
    float linear;
    float quadratic;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


struct FlashLight {
    PointLight point;
    vec3  direction;
    float cutOff;
    float outerCutOff;
};

out vec4 FragColor;

in vec2 texCoord;
in vec3 fragPos;
in vec3 norm;

#define NR_POINT_LIGHTS 4

uniform vec3 cameraPos;
uniform Material material;

uniform DirLight dirlight;
uniform PointLight pointlight[NR_POINT_LIGHTS];
uniform FlashLight flashlight;

vec3 CalcDirLight(DirLight light);
vec3 CalcPointLight(PointLight light);
vec3 CalcFlashLight(FlashLight light);

void main()
{
	vec3 result;

	//result = CalcDirLight(dirlight);

	//for(int i = 0; i < NR_POINT_LIGHTS; i++)
     //   result += CalcPointLight(pointlight[i]);

    //result += CalcFlashLight(flashlight);    
    
    //FragColor = vec4(result, 1.0);
	FragColor = vec4(1.0f, 1.0f,1.0f, 1.0f);
}

vec3 CalcDirLight(DirLight light)
{
	// 环境光
	vec3 ambient = light.ambient * texture(material.diffuse0, texCoord).rgb;
  	
    // 漫反射 
    vec3 norm = normalize(norm);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse0, texCoord).rgb;  
    
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
		specular = light.specular * spec * texture(material.specular0, texCoord).rgb;  
	}
    
    return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight light)
{
	// 环境光
	vec3 ambient = light.ambient * texture(material.diffuse0, texCoord).rgb;
  	
    // 漫反射 
    vec3 norm = normalize(norm);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse0, texCoord).rgb;  
    
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
		specular = light.specular * spec * texture(material.specular0, texCoord).rgb;  
	}
    
	float distance    = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + 
                light.quadratic * (distance * distance));
    vec3 result = ambient + diffuse + specular;
	return result * attenuation;
}

vec3 CalcFlashLight(FlashLight light)
{
	// 环境光
	vec3 ambient = light.point.ambient * texture(material.diffuse0, texCoord).rgb;
  	
    // 漫反射 
    vec3 norm = normalize(norm);
    vec3 lightDir = normalize(light.point.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.point.diffuse * diff * texture(material.diffuse0, texCoord).rgb;  
    
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
		specular = light.point.specular * spec * texture(material.specular0, texCoord).rgb;  
	}
    
	float distance    = length(light.point.position - fragPos);
	float attenuation = 1.0 / (light.point.constant + light.point.linear * distance + 
                light.point.quadratic * (distance * distance));

	float theta     = dot(lightDir, normalize(-light.direction));
	float epsilon   = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 result = ambient + diffuse + specular;
	return result * attenuation * intensity;
}