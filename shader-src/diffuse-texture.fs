uniform sampler2D texture;

void main (void) 
{
    vec4 color;
    color = gl_Color*2.0;
    color *= texture2D(texture, gl_TexCoord[0].xy);
    color=clamp(color,0.0,1.0);
    gl_FragColor = color;
}