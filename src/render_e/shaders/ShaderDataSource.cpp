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

Shader *ShaderDataSource::LoadLinkShader(char* name, ShaderLoadStatus &outStatus){
    char *vertexData;
    char *fragmentData;
    ShaderLoadStatus status = LoadShaderSource(name, &vertexData, &fragmentData);
    if (status != SHADER_OK){
        outStatus = status;
        return NULL;
    }
    Shader* shader = new Shader(vertexData, fragmentData);
    shader->Compile();
    shader->Link();
    return shader;
}
}
