#version 110
uniform vec3 color;
uniform int lightCount;

varying vec3 eye;
varying vec3 normal;
varying vec3 lights[8];

void main(){
    gl_Position = ftransform();
    normal = gl_Normal;

	vec4 eyePosition = gl_ModelViewMatrix * gl_Vertex;
	eye = -eyePosition.xyz;
}