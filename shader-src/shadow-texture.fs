uniform sampler2DShadow shadowMap;
uniform sampler2D texture;


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

    color *= texture2D(texture, gl_TexCoord[0].xy);
    color=clamp(color,0.0,1.0);
     gl_FragColor = color;
}