/* 
 * File:   DefaultShaders.cpp
 * Author: morten
 * 
 * Created on November 26, 2010, 3:49 PM
 */

#include "DefaultShaders.h"
#include <string>
#include "ShaderFileDataSource.h"

namespace render_e {

DefaultShaders *DefaultShaders::s_instance = NULL;

DefaultShaders::DefaultShaders():zOnly(NULL) {
}

DefaultShaders::~DefaultShaders() {
}

Shader *DefaultShaders::GetZOnly(){
    if (zOnly == NULL){
        ShaderFileDataSource sfd;
        ShaderLoadStatus status = SHADER_FILE_NOT_FOUND;
        zOnly = sfd.LoadLinkShader("zonly", status);
    }
    return zOnly;
}


Shader *DefaultShaders::GetDiffuseColor(){
    if (diffuseColor == NULL){
        ShaderFileDataSource sfd;
        ShaderLoadStatus status = SHADER_FILE_NOT_FOUND;
        diffuseColor = sfd.LoadLinkShader("diffuse-color", status);
    }
    return diffuseColor;
}

Shader *DefaultShaders::GetDiffuseTexture(){
    if (diffuseTexture == NULL){
        ShaderFileDataSource sfd;
        ShaderLoadStatus status = SHADER_FILE_NOT_FOUND;
        diffuseTexture = sfd.LoadLinkShader("diffuse-texture", status);
    }
    return diffuseTexture;
}
}
