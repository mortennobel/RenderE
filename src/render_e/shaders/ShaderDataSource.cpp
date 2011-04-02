/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#include "ShaderDataSource.h"
#include <string>

namespace render_e {
ShaderDataSource::ShaderDataSource() {
}

ShaderDataSource::ShaderDataSource(const ShaderDataSource& orig) {
}

ShaderDataSource::~ShaderDataSource() {
}

Shader *ShaderDataSource::LoadLinkShader(const char* name, ShaderLoadStatus &outStatus){
    using std::string;
    static string sharedVertexData;
    static string sharedFragmentData;
    if (sharedVertexData.length()==0 || sharedFragmentData.length()==0){
        LoadSharedSource(sharedVertexData,sharedFragmentData);
    }
    
    string vertexData;
    string fragmentData;
    outStatus = LoadShaderSource(name, vertexData, fragmentData);
    if (outStatus != SHADER_OK){
        return NULL;
    }
    Shader* shader = new Shader(vertexData.c_str(), fragmentData.c_str(), 
            sharedVertexData.c_str(), sharedFragmentData.c_str());
    outStatus = shader->CompileAndLink();
    if (outStatus != SHADER_OK){
        delete shader;
        return NULL;
    }
    return shader;
}
}
