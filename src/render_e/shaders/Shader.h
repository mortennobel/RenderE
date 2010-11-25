/* 
 * File:   Shader.h
 * Author: morten
 *
 * Created on November 14, 2010, 10:07 PM
 */

#ifndef SHADER_H
#define	SHADER_H

namespace render_e {
class Shader {
public:
    Shader(char *vertexShaderSource, char *fragmentShaderSource);
    virtual ~Shader();
    bool Compile();
    bool Link();
    void Bind();
    void SetTexture(unsigned int index, unsigned int textureId);
    void SetVector3(unsigned int index, float *vector);
    void SetVector4(unsigned int index, float *vector);
    void SetMatrix44(unsigned int index, float *mat);
private:
    Shader(const Shader& orig); // disallow copy constructor
    Shader& operator = (const Shader&); // disallow copy constructor
    
    int shaderid;
    char *vertexShaderSource;
    char *fragmentShaderSource;
};
}
#endif	/* SHADER_H */

