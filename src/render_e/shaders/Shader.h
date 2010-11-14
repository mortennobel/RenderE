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
    Shader(char *shaderSource);
    virtual ~Shader();
    bool Compile();
    bool Link();
    
    void Bind();
private:
    Shader(const Shader& orig); // disallow copy constructor
    Shader& operator = (const Shader&); // disallow copy constructor
   
    int shaderid;
    char *shaderSource;
};
}
#endif	/* SHADER_H */

