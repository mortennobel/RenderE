#version 110
uniform int lightCount;
uniform vec4 color;

varying vec3 normal;
varying vec3 eye;
varying vec3 lights[8];

const float shininess = 50.0;

void main(){
    vec3 nNormal = normalize(normal);
    vec3 nEye = normalize(eye);
    
    vec4 ambient = vec4(0.0,0.0,0.0,0.0);
    vec4 diffuse = vec4(0.0,0.0,0.0,0.0);
    vec4 specular= vec4(0.0,0.0,0.0,0.0);

    vec4 color4 = vec4(color.x,color.y,color.z, 1);

    for (int i=0;i<lightCount;i++){
        vec3 light = normalize(lights[i]);
        vec3 nHalf = normalize(nEye + light);

        float f = 1.0;

        float Kd = max(dot(nNormal, light), 0.0);
        float Ks = pow(max(dot(nHalf, nNormal), 0.0), shininess);


        // calculate light attenuation
 //       vec3 lightVec = (vec3(gl_LightSource[i].position) - eyeCoord);
        // compute distance between the surface and the light position
 //       float d = length(lightVec);
 //       float attenuation = 1.0 / (gl_LightSource[i].constantAttenuation +
 //           gl_LightSource[i].linearAttenuation * d +
 //           gl_LightSource[i].quadraticAttenuation * d * d);
        float attenuation = 1.0;
        

        diffuse = diffuse+ Kd * gl_LightSource[i].diffuse;
        if (dot(nNormal, light)<0.0) f = 0.0;
        specular = specular+f*Ks*gl_LightSource[i].specular;
        ambient = ambient+gl_LightSource[i].ambient;
    }
    
    gl_FragColor = color4*min(ambient + diffuse + specular, vec4(1,1,1,1));
}