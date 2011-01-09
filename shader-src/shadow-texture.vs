uniform mat4 textureMatrix;

varying vec3 transformedNormal;
varying vec4 ecPosition;
varying vec4 shadowTexCoord;

void main (void)
{	
	// Eye-coordinate position of vertex, needed in various calculations
	ecPosition = gl_ModelViewMatrix * gl_Vertex;

	// Do fixed functionality vertex transform
	gl_Position = ftransform();
	transformedNormal = fnormal();


	//Enable texture coordinates
	gl_TexCoord[0] = gl_MultiTexCoord0;

	shadowTexCoord = textureMatrix * gl_Vertex;
}