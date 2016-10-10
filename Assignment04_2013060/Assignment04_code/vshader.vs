#version 120
attribute vec3 vVertex;
attribute vec3 vColor;
attribute vec3 vNormal;

uniform mat4 vModel;
uniform mat4 vView;
uniform mat4 vProjection;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

varying vec3 fColor;

void main(void) {
	gl_Position = vProjection * vView * vModel * vec4(vVertex, 1.0);


	float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;


    vec3 norm = normalize(vNormal);
	vec3 lightDir = normalize(lightPos - vVertex);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float specularStrength = 1.0;
	vec3 viewDir = normalize(viewPos - vVertex);
	vec3 reflectDir = normalize(reflect(-lightDir, norm));
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;




	fColor =  (ambient + diffuse + specular) * vColor;
}
