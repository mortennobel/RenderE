uniform sampler2DShadow shadowMap;
uniform vec3 fcolor;

// the value to move one pixel
uniform float pixelOffsetX;
uniform float pixelOffsetY;

varying vec4 shadowTexCoord;
varying vec3 transformedNormal;
varying vec4 ecPosition;

float lookup( vec2 offSet)
{
	// Values are multiplied by shadowTexCoord.w because shadow2DProj does a W division for us.
	return shadow2DProj(shadowMap, shadowTexCoord + vec4(offSet.x * pixelOffsetX * shadowTexCoord.w, offSet.y * pixelOffsetY * shadowTexCoord.w,-0.005, 0.0) ).w;
}

void main (void) 
{

    vec4 color;
    vec3 n = normalize(transformedNormal);

    float invShadow = 0;
	
	// 8x8 PCF-wide kernel (10 steps instead of 1)
	float x,y;
	for (y = -30.5 ; y <=30.5 ; y+=10.0)
		for (x = -30.5 ; x <=30.5 ; x+=10.0)
			invShadow += lookup(vec2(x,y));
	
	invShadow /= 64.0 ;
   
	flight(n, ecPosition, 1.0, invShadow, color); 

    color *=vec4(fcolor.r,fcolor.g,fcolor.b,1.0);
    color=clamp(color,0.0,1.0);
     gl_FragColor = color;
}