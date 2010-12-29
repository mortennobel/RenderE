/* 
 * File:   ShaderDataSource.cpp
 * Author: morten
 * 
 * Created on November 14, 2010, 10:07 PM
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
    string vertexData;
    string fragmentData;
    outStatus = LoadShaderSource(name, vertexData, fragmentData);
    if (outStatus != SHADER_OK){
        return NULL;
    }
    Shader* shader = new Shader(vertexData.c_str(), fragmentData.c_str());
    outStatus = shader->Compile();
    if (outStatus != SHADER_OK){
        delete shader;
        return NULL;
    }
    outStatus = shader->Link();
    if (outStatus != SHADER_OK){
        delete shader;
        return NULL;
    }
    return shader;
}
}
