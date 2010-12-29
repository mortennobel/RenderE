/* 
 * File:   Material.cpp
 * Author: morten
 * 
 * Created on November 14, 2010, 10:50 PM
 */

#include "Material.h"
#include <iostream>

using namespace std;

namespace render_e {
Material::Material(Shader *shader)
:Component(MaterialType), shader(shader) {
}

Material::~Material() {
}

void Material::Bind(){
    shader->Bind();
}

void Material::SetVector2(std::string name, Vector2 vec){
    cout<<"Not implemented"<<endl;
}
void Material::SetVector3(std::string name, Vector3 vec){
    cout<<"Not implemented"<<endl;
}
void Material::SetVector4(std::string name, Vector4 vec){
    cout<<"Not implemented"<<endl;
}
void Material::SetFloat(std::string name, float f){
    cout<<"Not implemented"<<endl;
}
void Material::SetTexture(std::string name, TextureBase *texture){
    cout<<"Not implemented"<<endl;
}
}
