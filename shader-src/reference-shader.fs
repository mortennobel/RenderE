// From http://www.blitzbasic.com/Community/posts.php?topic=65243
uniform sampler2D texture0;

void main (void) 
{
    vec4 color;
    color = gl_Color*2.0;
    color *= texture2D(texture0, gl_TexCoord[0].xy);
	color=clamp(color,0.0,1.0);
    gl_FragColor = color;
}