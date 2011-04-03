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

class ShaderDataSource; // Forward decl

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
    static Shader *CreateShader(std::string assetName, std::string shaderName, ShaderDataSource *shaderDataSource, ShaderLoadStatus &outLoadStatus);
    
    virtual ~Shader();
    
    void Bind();
    /// Reloads the shader from the shader source
    ///
    ShaderLoadStatus Reload();
    void Unload();
    void SetTexture(unsigned int index, unsigned int textureId);
    void SetVector3(unsigned int index, float *vector);
    void SetVector4(unsigned int index, float *vector);
    void SetMatrix44(unsigned int index, float *mat);
    std::string GetShaderName() {return shaderName; }
    /** Returns -1 if not found */
    int GetUniformLocation(const char *location);
    
    void IncreaseUsageCount() { usageCount++; }
    void DecreaseUsageCount() { usageCount--; }
    int GetUsageCount() { return usageCount;}
private:
    Shader(std::string shaderName, std::string assetName, ShaderDataSource *shaderDataSource);
    ShaderLoadStatus CompileAndLink(std::string sharedVertexData,std::string sharedFragmentData,
        std::string vertexData,std::string fragmentData);
    ShaderLoadStatus Compile(std::string sharedVertexData,std::string sharedFragmentData,
        std::string vertexData,std::string fragmentData);
    ShaderLoadStatus Link();
    Shader(const Shader& orig); // disallow copy constructor
    Shader& operator = (const Shader&); // disallow copy constructor
    
    unsigned int shaderProgramId;
    unsigned int vertexShaderId;
    unsigned int fragmentShaderId;
    
    int usageCount;
    std::string shaderName;
    std::string assetName;
    ShaderDataSource *shaderDataSource;
};
}
#endif	/* SHADER_H */

