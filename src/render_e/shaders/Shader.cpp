/* 
 * File:   Shader.cpp
 * Author: morten
 * 
 * Created on November 14, 2010, 10:07 PM
 */

#include "Shader.h"
#include "GL/glew.h"

#include <iostream>
#ifdef _WIN32
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

namespace render_e {
Shader::Shader(const char *vertexShaderSource, const char *fragmentShaderSource)
:vertexShaderSource(vertexShaderSource),fragmentShaderSource(fragmentShaderSource),shaderProgramId(0),vertexShaderId(0),fragmentShaderId(0) {
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
}

void checkInfoLogShader(unsigned int shaderId){
    int infologlength;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infologlength);
    if (infologlength>0){
        char infoLog[infologlength+1];
        glGetShaderInfoLog(shaderId,infologlength,&infologlength,infoLog);
        std::cout<<infoLog<<std::endl;
    }
}

ShaderLoadStatus Shader::Compile(){
    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    if (vertexShaderId == 0 || fragmentShaderId == 0){
        return SHADER_CANNOT_ALLOCATE;
    }
    
    // Load shader sources
    glShaderSource(vertexShaderId, 1, &vertexShaderSource, NULL);
    glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, NULL);

    // Compile the shaders
    int compileStatus = 0;
    glCompileShader(vertexShaderId);
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &compileStatus);
    if (!compileStatus){
        return SHADER_COMPILE_ERROR_VERTEX_SHADER;
    }
    glCompileShader(fragmentShaderId);
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &compileStatus);
    if (!compileStatus){
        return SHADER_COMPILE_ERROR_FRAGMENT_SHADER;
    }
    // check info log
    checkInfoLogShader(vertexShaderId);
    checkInfoLogShader(fragmentShaderId);
    
    return SHADER_OK;
}

void checkInfoLogProgram(unsigned int programId){
    int infologlength;
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infologlength);
    if (infologlength>0){
        char infoLog[infologlength+1];
        glGetProgramInfoLog(programId,infologlength,&infologlength,infoLog);
        std::cout<<infoLog<<std::endl;
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
        return SHADER_LINK_ERROR;
    }
    
    return SHADER_OK;
}
    
void Shader::Bind(){
    glUseProgram(shaderProgramId);
}
}
