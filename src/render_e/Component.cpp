/* 
 * File:   Component.cpp
 * Author: morten
 * 
 * Created on November 8, 2010, 10:32 PM
 */

#include "Component.h"


namespace render_e {

Component::Component(ComponentType componentType)
:componentType(componentType) {
}

Component::~Component() {
}

SceneObject *Component::GetOwner(){
    return owner;
}

void Component::SetOwner(SceneObject *owner){
    this->owner = owner;
}

}