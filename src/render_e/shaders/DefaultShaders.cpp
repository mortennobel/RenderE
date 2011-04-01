/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
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
        char zOnlyFilename[] = "zonly";
        zOnly = sfd.LoadLinkShader(zOnlyFilename, status);
    }
    return zOnly;
}


Shader *DefaultShaders::GetDiffuseColor(){
    if (diffuseColor == NULL){
        ShaderFileDataSource sfd;
        ShaderLoadStatus status = SHADER_FILE_NOT_FOUND;
        char filename[] = "diffuse-color";
        diffuseColor = sfd.LoadLinkShader(filename, status);
    }
    return diffuseColor;
}

Shader *DefaultShaders::GetDiffuseTexture(){
    if (diffuseTexture == NULL){
        ShaderFileDataSource sfd;
        ShaderLoadStatus status = SHADER_FILE_NOT_FOUND;
        char filename[] = "diffuse-texture";
        diffuseTexture = sfd.LoadLinkShader(filename, status);
    }
    return diffuseTexture;
}
}
