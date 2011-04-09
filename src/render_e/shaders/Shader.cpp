/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#include "Shader.h"
#include "GL/glew.h"

#include <sstream>
#include <string>
#ifdef _WIN32
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif
#include "ShaderDataSource.h"
#include "../Log.h"

namespace render_e {

Shader *Shader::CreateShader(std::string assetName, std::string shaderName, ShaderDataSource *shaderDataSource, ShaderLoadStatus &outLoadStatus){
    Shader* shader = new Shader(shaderName, assetName, shaderDataSource);
    outLoadStatus = shader->Reload();
    if (outLoadStatus != SHADER_OK){
        delete shader;
        return NULL;
    }
    return shader;
}

Shader::Shader(
        std::string shaderName, std::string assetName, ShaderDataSource *shaderDataSource)
:shaderProgramId(0),vertexShaderId(0),fragmentShaderId(0), 
        shaderName(shaderName), assetName(assetName), shaderDataSource(shaderDataSource) {
}

Shader::~Shader() {
    Unload();
    // do not delete sharedShaderLib, since that is shared between different 
    // shader instances
}

void checkInfoLogShader(unsigned int shaderId){
    int infologlength;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infologlength);
    if (infologlength>0){
        char *infoLog = new char[infologlength+1];
        glGetShaderInfoLog(shaderId,infologlength,&infologlength,infoLog);
        INFO(infoLog);
		delete []infoLog;
    }
}

ShaderLoadStatus Shader::CompileAndLink(std::string sharedVertexData,std::string sharedFragmentData,
        std::string vertexData,std::string fragmentData){
    ShaderLoadStatus status = Compile(sharedVertexData, sharedFragmentData,
        vertexData, fragmentData);
    if (status != SHADER_OK) return status;
    status = Link();
    return status;
}

ShaderLoadStatus Shader::Compile(std::string sharedVertexData,std::string sharedFragmentData,
        std::string vertexData,std::string fragmentData){
    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    
    // concatenate shaders into one file
    // It should be possible to compile files independently and link them
    // together, but it seems to be a bit buggy
    using namespace std;
    string vShader;
    string fShader;
    vShader.append(sharedVertexData);
    vShader.append(vertexData);
    
    fShader.append(sharedFragmentData);
    fShader.append(fragmentData);
    
    int shaderIds[4] = {
        vertexShaderId,
        fragmentShaderId,    
    };
    
    const char *shaderSource[] = {
        vShader.c_str(),
        fShader.c_str(),
    };
    const char *shaderSourceName[] = {
        "vertexShaderSource",
        "fragmentShaderSource",
    };
    
    for (int i=0;i<2;i++){
        if (shaderIds[i] == 0){
            return SHADER_CANNOT_ALLOCATE;
        }
        glShaderSource(shaderIds[i], 1, &(shaderSource[i]), NULL);
        
        int compileStatus = 0;
        glCompileShader(shaderIds[i]);
        glGetShaderiv(shaderIds[i], GL_COMPILE_STATUS, &compileStatus);
        checkInfoLogShader(shaderIds[i]);
        if (!compileStatus){
            stringstream ss;
            ss<<"Cannot compile shader "<<shaderSourceName[i];
            ERROR(ss.str());
            return SHADER_COMPILE_ERROR_VERTEX_SHADER;
        }
    }
    
    return SHADER_OK;
}

void checkInfoLogProgram(unsigned int programId){
    int infologlength;
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infologlength);
    if (infologlength>0){
        char *infoLog = new char[infologlength+1];
        glGetProgramInfoLog(programId,infologlength,&infologlength,infoLog);
        INFO(infoLog);
		delete [] infoLog;
    }
}

ShaderLoadStatus Shader::Link(){
    shaderProgramId = glCreateProgram();
    
    if (shaderProgramId == 0) {
        return SHADER_CANNOT_ALLOCATE;
    }
    
    // Attach the shader objects to the program object
    glAttachShader(shaderProgramId, vertexShaderId);
    glAttachShader(shaderProgramId, fragmentShaderId);
    
    glLinkProgram(shaderProgramId);
    checkInfoLogProgram(shaderProgramId);
    
    int linkStatus = 0;
    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &linkStatus);
    if (!linkStatus){
        using namespace std;
        ERROR("Link error");
        return SHADER_LINK_ERROR;
    }
    
    return SHADER_OK;
}
    
void Shader::Bind(){
    glUseProgram(shaderProgramId);
}

ShaderLoadStatus Shader::Reload(){
    Unload();
    std::string sharedVertexData;
    std::string sharedFragmentData;
    if (sharedVertexData.length()==0 || sharedFragmentData.length()==0){
        shaderDataSource->LoadSharedSource(sharedVertexData,sharedFragmentData);
    }
    std::string vertexData;
    std::string fragmentData;
    ShaderLoadStatus loadStatus = shaderDataSource->LoadShaderSource(assetName.c_str(), vertexData, fragmentData);
    if (loadStatus != SHADER_OK){
        return loadStatus;
    }
    loadStatus = CompileAndLink(sharedVertexData, sharedFragmentData,
        vertexData, fragmentData);
    return loadStatus;
}

void Shader::Unload(){
    if (fragmentShaderId != 0) {
        glDeleteShader(fragmentShaderId);
        fragmentShaderId = 0;
    }
    if (vertexShaderId != 0) {
        glDeleteShader(vertexShaderId);
        vertexShaderId = 0;
    }
    if (shaderProgramId != 0) {
        glDeleteProgram(shaderProgramId);
        shaderProgramId = 0;
    }
}

int Shader::GetUniformLocation(const char *location){
    return glGetUniformLocation(shaderProgramId, location);
}
}
