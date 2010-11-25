/* 
 * File:   Shader.cpp
 * Author: morten
 * 
 * Created on November 14, 2010, 10:07 PM
 */

#include "Shader.h"

namespace render_e {
Shader::Shader(char *vertexShaderSource, char *fragmentShaderSource)
:vertexShaderSource(vertexShaderSource),fragmentShaderSource(fragmentShaderSource) {
}

Shader::~Shader() {
}

bool Shader::Compile(){

}

bool Shader::Link(){
}
    
void Shader::Bind(){
}
}
