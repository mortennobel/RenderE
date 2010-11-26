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
}
