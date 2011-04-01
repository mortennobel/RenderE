/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#include "Component.h"
#include <cstring>


namespace render_e {

Component::Component(ComponentType componentType)
:componentType(componentType),owner(NULL) {
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