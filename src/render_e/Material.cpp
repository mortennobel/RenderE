/* 
 * File:   Material.cpp
 * Author: morten
 * 
 * Created on November 14, 2010, 10:50 PM
 */

#include "Material.h"
#include <iostream>
#include <cassert>
#include <GL/glew.h>

using namespace std;

namespace render_e {
Material::Material(Shader *shader)
:Component(MaterialType), shader(shader) {
}

Material::~Material() {
}

void Material::Bind(){
    shader->Bind();
    
    std::vector<ShaderParameters>::iterator iter =  parameters.begin();
    for (;iter != parameters.end();iter++){
        switch ((*iter).paramType){
            case SPT_FLOAT:
                glUniform1fv((*iter).id,1, (*iter).shaderValue.f);
                break;
            case SPT_VECTOR2:
                glUniform2fv((*iter).id,1, (*iter).shaderValue.f);
                break;
            case SPT_VECTOR3:
                glUniform3fv((*iter).id,1, (*iter).shaderValue.f);
                break;
            case SPT_VECTOR4:
                glUniform4fv((*iter).id,1, (*iter).shaderValue.f);
                break;
            case SPT_INT:
                glUniform1iv((*iter).id,1, &((*iter).shaderValue.integer));
                break;
        }
    }
}

void Material::AddParameter(ShaderParameters &param){
    // replace a existing parameter
    std::vector<ShaderParameters>::iterator iter = parameters.begin();
    for (;iter != parameters.end();iter++){
        if ((*iter).id == param.id){
            (*iter).shaderValue.f[0] = param.shaderValue.f[0];
            (*iter).shaderValue.f[1] = param.shaderValue.f[1];
            (*iter).shaderValue.f[2] = param.shaderValue.f[2];
            (*iter).shaderValue.f[3] = param.shaderValue.f[3];
            assert ((*iter).paramType == param.paramType); // assume parameter type
            return;
        }
    }
    // parameter not found - add new
    parameters.push_back(param);
}

bool Material::SetVector2(std::string name, Vector2 vec){
    int id = shader->GetUniformLocation(name.c_str());
    if (id==-1){
        return false;
    }
    ShaderParameters param;
    param.id = id;
    param.paramType = SPT_VECTOR2;
    param.shaderValue.f[0] = vec[0];
    param.shaderValue.f[1] = vec[1];
    AddParameter(param);
}

bool Material::SetVector3(std::string name, Vector3 vec){
    int id = shader->GetUniformLocation(name.c_str());
    if (id==-1){
        return false;
    }
    ShaderParameters param;
    param.id = id;
    param.paramType = SPT_VECTOR3;
    param.shaderValue.f[0] = vec[0];
    param.shaderValue.f[1] = vec[1];
    param.shaderValue.f[2] = vec[2];
    AddParameter(param);
}

bool Material::SetVector4(std::string name, Vector4 vec){
    int id = shader->GetUniformLocation(name.c_str());
    if (id==-1){
        return false;
    }
    ShaderParameters param;
    param.id = id;
    param.paramType = SPT_VECTOR4;
    param.shaderValue.f[0] = vec[0];
    param.shaderValue.f[1] = vec[1];
    param.shaderValue.f[2] = vec[2];
    param.shaderValue.f[3] = vec[3];
    AddParameter(param);
}

bool Material::SetFloat(std::string name, float f){
    int id = shader->GetUniformLocation(name.c_str());
    if (id==-1){
        return false;
    }
    ShaderParameters param;
    param.id = id;
    param.paramType = SPT_FLOAT;
    param.shaderValue.f[0] = f;
    AddParameter(param);
}

bool Material::SetTexture(std::string name, TextureBase *texture){
    int id = shader->GetUniformLocation(name.c_str());
    if (id==-1){
        return false;
    }
    ShaderParameters param;
    param.id = id;
    param.paramType = SPT_FLOAT;
    param.shaderValue.integer = texture->GetTextureId();
    AddParameter(param);
}

bool Material::SetInt(std::string name, int i){
    int id = shader->GetUniformLocation(name.c_str());
    if (id==-1){
        return false;
    }
    ShaderParameters param;
    param.id = id;
    param.paramType = SPT_INT;
    param.shaderValue.integer = i;
    AddParameter(param);
}
}
