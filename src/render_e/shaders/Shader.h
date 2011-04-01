/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#ifndef SHADER_H
#define	SHADER_H

#include <string>

namespace render_e {

enum ShaderLoadStatus {
    SHADER_OK,
    SHADER_CANNOT_ALLOCATE,
    SHADER_FILE_NOT_FOUND,
    SHADER_COMPILE_ERROR_VERTEX_SHADER,
    SHADER_COMPILE_ERROR_FRAGMENT_SHADER,
    SHADER_LINK_ERROR    
};

class Shader {
public:
    Shader(const char *vertexShaderSource, const char *fragmentShaderSource,
        const char *sharedVertexShaderLib,
        const char *sharedFragmentShaderLib);
    virtual ~Shader();
    ShaderLoadStatus Compile();
    ShaderLoadStatus Link();
    void Bind();
    void SetTexture(unsigned int index, unsigned int textureId);
    void SetVector3(unsigned int index, float *vector);
    void SetVector4(unsigned int index, float *vector);
    void SetMatrix44(unsigned int index, float *mat);
    void SetName(std::string name) { this->name = name;}
    std::string GetName() {return name; }
    /** Returns -1 if not found */
    int GetUniformLocation(const char *location);
private:
    Shader(const Shader& orig); // disallow copy constructor
    Shader& operator = (const Shader&); // disallow copy constructor
    
    unsigned int shaderProgramId;
    unsigned int vertexShaderId;
    unsigned int fragmentShaderId;
    
    const char *vertexShaderSource;
    const char *fragmentShaderSource;
    const char *sharedVertexShaderLib;
    const char *sharedFragmentShaderLib;
    std::string name;
};
}
#endif	/* SHADER_H */

