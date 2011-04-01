/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#include "Material.h"
#include <iostream>
#include <cassert>
#include <GL/glew.h>
#include "Camera.h"

using namespace std;

namespace render_e {
Material::Material(Shader *shader)
:Component(MaterialType), shader(shader) {
}

Material::~Material() {
}

void Material::Bind(){
    shader->Bind();
    int textureIndex = 0;
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
                glUniform1i((*iter).id, (*iter).shaderValue.integer[0]);
                break;
            case SPT_TEXTURE:
                glActiveTexture(GL_TEXTURE0+textureIndex);
                glBindTexture( (*iter).shaderValue.integer[1], (*iter).shaderValue.integer[0] );
                glUniform1i((*iter).id, textureIndex);
                textureIndex++;
                break;
			case SPT_SHADOW_SETUP_NAME:
				{
					SceneObject *sceneObj = GetOwner()->GetRenderBase()->Find((*iter).shaderValue.cameraName);
					if (sceneObj==NULL){
						cout << "Cannot find shadow setup name "<<(*iter).shaderValue.cameraName<<endl;
						continue;
					}
					Camera *cam = sceneObj->GetCamera();
					if (cam==NULL){
						cout << "Cannot find shadow setup name "<<(*iter).shaderValue.cameraName<<" has no camera attached"<<endl;
						continue;
					}
					// clean up
					delete [] (*iter).shaderValue.cameraName;
					// change type
					(*iter).paramType = SPT_SHADOW_SETUP;
					(*iter).shaderValue.camera = cam;
				}
				break;
			case SPT_SHADOW_SETUP:
				glm::mat4 m = GetOwner()->GetTransform()->GetLocalTransform();
				float *shadowMatrix = (*iter).shaderValue.camera->GetShadowMatrix(m);
				glUniformMatrix4fv((*iter).id,1,false, shadowMatrix);
				break;
        }
    }
}

Material *Material::Instance(){
	Material *res = new Material(shader);
	res->textures = textures;
	res->name = name;
	for (int i=0;i<parameters.size();i++){
		ShaderParameters p = parameters[i];
		if (p.paramType==SPT_SHADOW_SETUP_NAME){
			int len = strlen(p.shaderValue.cameraName)+1;
			char *nameCopy = new char[len];
			strncpy(nameCopy, p.shaderValue.cameraName,len);
			p.shaderValue.cameraName = nameCopy;
		}
		res->parameters.push_back(p);
	}
	res->name.append("_instance");

	return res;
}

void Material::AddParameter(ShaderParameters &param){
    // replace a existing parameter
    std::vector<ShaderParameters>::iterator iter = parameters.begin();
    for (;iter != parameters.end();iter++){
        if ((*iter).id == param.id){
            memcpy(&((*iter).shaderValue), &(param.shaderValue), sizeof(ShaderParameters));
            return;
        }
    }
    // parameter not found - add new
    parameters.push_back(param);
}

bool Material::SetVector2(std::string name, glm::vec2 vec){
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


bool Material::SetShadowSetup(std::string name, const char *cameraName){
	int id = shader->GetUniformLocation(name.c_str());
    if (id==-1){
        return false;
    }
	ShaderParameters param;
    param.id = id;
    param.paramType = SPT_SHADOW_SETUP_NAME;
	int nameLen = strlen(cameraName);
	char *nameCopy = new char[nameLen+1];
	strncpy(nameCopy, cameraName, nameLen+1);
    param.shaderValue.cameraName = nameCopy;
    AddParameter(param);
}

bool Material::SetVector3(std::string name, glm::vec3 vec){
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

bool Material::SetVector4(std::string name, glm::vec4 vec){
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
    param.paramType = SPT_TEXTURE;
    param.shaderValue.integer[0] = texture->GetTextureId();
    param.shaderValue.integer[1] = texture->GetTextureType();
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
    param.shaderValue.integer[0] = i;
    AddParameter(param);
}
}
