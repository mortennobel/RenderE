void main (void)
{
	vec3  transformedNormal;
	float alphaFade = 1.0;

	// Eye-coordinate position of vertex, needed in various calculations
	vec4 ecPosition = gl_ModelViewMatrix * gl_Vertex;

	// Do fixed functionality vertex transform
	gl_Position = ftransform();
	transformedNormal = fnormal();
	flight(transformedNormal, ecPosition, alphaFade);

	//Enable texture coordinates
	gl_TexCoord[0] = gl_MultiTexCoord0;
	//gl_TexCoord[1] = gl_MultiTexCoord1;
	//gl_TexCoord[2] = gl_MultiTexCoord2;
	//gl_TexCoord[3] = gl_MultiTexCoord3;

}