#version 120
attribute vec3 vVertex;
attribute vec3 vColor;
attribute vec3 vNormal;

uniform mat4 vModel;
uniform mat4 vView;
uniform mat4 vProjection;

varying vec3 fColor;
varying vec3 Normal;
varying vec3 FragPos;

void main(void) {
	gl_Position = vProjection * vView * vModel * vec4(vVertex, 1.0);
	fColor = vColor; //Interpolate color
	Normal = vNormal;
	FragPos = vec3(vModel * vec4(vVertex, 1.0f));
}