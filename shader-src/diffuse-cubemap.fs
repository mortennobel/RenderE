varying vec3 normal;
uniform samplerCube texture;

void main (void) 
{
    vec4 color;
    color = gl_Color*2.0;
    color *= textureCube(texture, normal*-1.0);
    color=clamp(color,0.0,1.0);
    gl_FragColor = color;
}
