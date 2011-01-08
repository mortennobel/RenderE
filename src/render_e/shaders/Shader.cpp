/* 
 * File:   Shader.cpp
 * Author: morten
 * 
 * Created on November 14, 2010, 10:07 PM
 */

#include "Shader.h"
#include "GL/glew.h"

#include <iostream>
#include <string>
#ifdef _WIN32
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

namespace render_e {
Shader::Shader(const char *vertexShaderSource, const char *fragmentShaderSource, 
        const char *sharedVertexShaderLib,
        const char *sharedFragmentShaderLib)
:vertexShaderSource(vertexShaderSource),
        fragmentShaderSource(fragmentShaderSource),
        sharedVertexShaderLib(sharedVertexShaderLib),
        sharedFragmentShaderLib(sharedFragmentShaderLib),
        shaderProgramId(0),vertexShaderId(0),fragmentShaderId(0) {
}

Shader::~Shader() {
    if (fragmentShaderId != 0) {
        glDeleteShader(fragmentShaderId);
    }
    if (vertexShaderId != 0) {
        glDeleteShader(vertexShaderId);
    }
    if (shaderProgramId != 0) {
        glDeleteProgram(shaderProgramId);
    }
    // do not delete sharedShaderLib, since that is shared between different 
    // shader instances
}

void checkInfoLogShader(unsigned int shaderId){
    int infologlength;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infologlength);
    if (infologlength>0){
        char *infoLog = new char[infologlength+1];
        glGetShaderInfoLog(shaderId,infologlength,&infologlength,infoLog);
        std::cout<<infoLog<<std::endl;
		delete []infoLog;
    }
}

ShaderLoadStatus Shader::Compile(){
    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    
    // concatenate shaders into one file
    // It should be possible to compile files independently and link them
    // together, but it seems to be a bit buggy
    using namespace std;
    string vShader;
    string fShader;
    vShader.append(sharedVertexShaderLib);
    vShader.append(vertexShaderSource);
    
    fShader.append(sharedFragmentShaderLib);
    fShader.append(fragmentShaderSource);
    
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
            std::cout<<"Cannot compile shader "<<shaderSourceName[i]<<std::endl;
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
        std::cout<<infoLog<<std::endl;
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
        cout<<"Link error"<<endl;
        return SHADER_LINK_ERROR;
    }
    
    return SHADER_OK;
}
    
void Shader::Bind(){
    glUseProgram(shaderProgramId);
}

int Shader::GetUniformLocation(const char *location){
    return glGetUniformLocation(shaderProgramId, location);
}
}
