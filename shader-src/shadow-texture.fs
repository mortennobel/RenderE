uniform sampler2DShadow shadowMap;
uniform sampler2D texture;


varying vec4 shadowTexCoord;
varying vec3 transformedNormal;
varying vec4 ecPosition;

void main (void) 
{
/*
    vec4 color;
    vec3 n = normalize(transformedNormal);

    float invShadow = shadow2DProj(shadowMap, shadowTexCoord).r;
	flight(n, ecPosition, 1.0, invShadow, color);
    
    color *= texture2D(texture, gl_TexCoord[0].xy);
    color=clamp(color,0.0,1.0);
    gl_FragColor = color;
    */


    vec4 shadowCoordinateWdivide = shadowTexCoord / shadowTexCoord.w ;
		
		// Used to lower moiré pattern and self-shadowing
		shadowCoordinateWdivide.z += 0.0005;
		
        gl_FragColor = clamp(vec4(shadowCoordinateWdivide.s, shadowCoordinateWdivide.t, 0.0,1.0),0.0,1.0);

		/*
		float distanceFromLight = texture2D(shadowMap,shadowCoordinateWdivide.st).z;
		
		
	 	float shadow = 1.0;
	 	if (shadowTexCoord.w > 0.0)
	 		shadow = distanceFromLight < shadowCoordinateWdivide.z ? 0.5 : 1.0 ;
	  	
		
		gl_FragColor =	 shadow * vec4(1.0,1.0,1.0,1.0);;
        */
}