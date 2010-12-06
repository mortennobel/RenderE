#version 110
const int lightCount = 8;
uniform vec3 color;

varying vec3 normal;
varying vec3 eye;
varying vec3 lights[8];

void main(){
    gl_FragColor = vec4(color,1);
}