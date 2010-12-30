/* 
 * File:   RenderObject.cpp
 * Author: morten
 * 
 * Created on October 31, 2010, 2:42 PM
 */

#include "SceneObject.h"
#include <cassert>
#include <iostream>
#include <GL/glew.h>

#include "Camera.h"
#include "Transform.h"

namespace render_e {

SceneObject::SceneObject()
:camera(NULL),mesh(NULL),material(NULL),transform(this),light(NULL) {
}

SceneObject::~SceneObject() {
}


Transform &SceneObject::GetTransform() { 
    return transform; 
}

Camera *SceneObject::GetCamera() { 
    return camera; 
}

MeshComponent *SceneObject::GetMesh(){ 
    return mesh; 
}

Material *SceneObject::GetMaterial(){
    return material;
}

Light *SceneObject::GetLight(){
    return light;
}
    
const std::vector<Component*> * SceneObject::GetComponents() const{
    return &components;
}

void SceneObject::RemoveComponent(Component* component){
    std::vector<Component*>::iterator iter = find(components.begin(), components.end(), component);
    if (iter != components.end()){
        components.erase(iter);
        switch (component->GetComponentType()){
            case TransformType:
                assert(false); // cannot have multiple 
                return;
                break;
            case MeshType:
                mesh = NULL;
                break;
            case CameraType:
                camera = NULL;
                break;
            case MaterialType:
                material = NULL;
                break;
            case LightComponentType:
                light = NULL;
                break;
        }
    }
    
}

void SceneObject::AddCompnent(Component* component){
    assert(component->GetOwner()==NULL); // Each component can only have one owner
    switch (component->GetComponentType()){
        case TransformType:
            assert(false); // cannot have multiple 
            return;
            break;
        case MeshType:
            assert(mesh==NULL);
            mesh = static_cast<MeshComponent*>(component);
            break;
        case CameraType:
            assert(camera==NULL);
            camera = static_cast<Camera*>(component);
            break;
        case MaterialType:
            assert(material==NULL);
            material = static_cast<Material*>(component);
            break;
        case LightComponentType:
            assert(light==NULL);
            light = static_cast<Light*>(component);
            break;
    }
    components.push_back(component);
    component->SetOwner(this);
}

void SceneObject::AddChild(SceneObject *sceneObject){
    this->transform.AddChild(&(sceneObject->transform));
}
}
