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
:camera(NULL),mesh(NULL) {
}

SceneObject::~SceneObject() {
}

const std::vector<Component*> * SceneObject::GetComponents() const{
    return &components;
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
            mesh = static_cast<Mesh*>(component);
            break;
        case CameraType:
            assert(camera==NULL);
            camera = static_cast<Camera*>(component);
            break;
    }
    components.push_back(component);
    component->SetOwner(this);
}
}
