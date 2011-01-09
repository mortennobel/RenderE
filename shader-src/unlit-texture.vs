void main (void)
{
	// Do fixed functionality vertex transform
	gl_Position = ftransform();

	//Enable texture coordinates
	gl_TexCoord[0] = gl_MultiTexCoord0;
}