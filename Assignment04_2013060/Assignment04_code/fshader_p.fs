#version 120

varying vec3 fColor;
varying vec3 Normal;
varying vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform vec3 lightPos2;
uniform vec3 lightColor2;

uniform vec3 viewPos;

void main(void) {
	float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;


    vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float specularStrength = 1.0;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = normalize(reflect(-lightDir, norm));
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 light1 = (ambient + diffuse + specular) * fColor;

	ambientStrength = 0.1f;
    ambient = ambientStrength * lightColor2;


    norm = normalize(Normal);
	lightDir = normalize(lightPos2 - FragPos);
	diff = max(dot(norm, lightDir), 0.0);
	diffuse = diff * lightColor2;

	specularStrength = 1.5;
	viewDir = normalize(viewPos - FragPos);
	reflectDir = normalize(reflect(-lightDir, norm));
	spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
	specular = specularStrength * spec * lightColor2;

	vec3 light2 = (ambient + diffuse + specular) * fColor;


	
    
	gl_FragColor = vec4(light1 + light2, 1.0);
}
