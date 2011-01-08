uniform vec4 color;

void main (void) 
{
    vec4 colorf;
    colorf = gl_Color*2.0;
    colorf *= color;
    colorf=clamp(colorf,0.0,1.0);
    gl_FragColor = colorf;
}