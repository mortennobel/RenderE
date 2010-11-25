/* 
 * File:   ShaderFileDataSource.cpp
 * Author: morten
 * 
 * Created on November 14, 2010, 10:12 PM
 */

#include "ShaderFileDataSource.h"

namespace render_e {
ShaderFileDataSource::ShaderFileDataSource() {
}

ShaderFileDataSource::ShaderFileDataSource(const ShaderFileDataSource& orig) {
}

ShaderFileDataSource::~ShaderFileDataSource() {
}

ShaderLoadStatus ShaderFileDataSource::LoadShaderSource(char* name, 
            char **vertexShaderData,
            char **fragmentShaderData){
    return SHADER_OK;
}
}
