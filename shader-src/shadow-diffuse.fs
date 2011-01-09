uniform sampler2DShadow shadowMap;
uniform vec3 fcolor;


varying vec4 shadowTexCoord;
varying vec3 transformedNormal;
varying vec4 ecPosition;

void main (void) 
{

    vec4 color;
    vec3 n = normalize(transformedNormal);

    float invShadow = 1;
    invShadow = shadow2DProj(shadowMap, shadowTexCoord+ vec4(0.0,0.0,-0.005, 0.0)).w;
	flight(n, ecPosition, 1.0, invShadow, color); 

    color *=vec4(fcolor.r,fcolor.g,fcolor.b,1.0);
    color=clamp(color,0.0,1.0);
     gl_FragColor = color;
}