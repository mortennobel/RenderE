/* 
 * File:   Material.cpp
 * Author: morten
 * 
 * Created on November 14, 2010, 10:50 PM
 */

#include "Material.h"
#include <iostream>

namespace render_e {
Material::Material(Shader *shader)
:Component(MaterialType), shader(shader) {
}

Material::~Material() {
}

void Material::Bind(){
    shader->Bind();
}
}
