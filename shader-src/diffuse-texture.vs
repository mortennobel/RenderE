#version 110
uniform int lightCount;

varying vec3 eye;
varying vec3 normal;
varying vec3 lights[8];

void main(){
    gl_Position = ftransform();
    normal = normalize(gl_NormalMatrix * gl_Normal);

    vec4 eyePosition = gl_ModelViewMatrix * gl_Vertex;
    eye = -eyePosition.xyz;

    for (int i=0;i<lightCount;i++){
        vec4 eyeLightPos = gl_LightSource[i].position;
        lights[i] = eyeLightPos.xyz-eyePosition.xyz;
    }

    gl_TexCoord[0] =  gl_MultiTexCoord0;
}