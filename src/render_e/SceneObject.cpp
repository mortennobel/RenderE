/* 
 * File:   RenderObject.cpp
 * Author: morten
 * 
 * Created on October 31, 2010, 2:42 PM
 */

#include "SceneObject.h"
#include <cassert>
#include <GL/glew.h>

#include "Transform.h"

namespace render_e {

SceneObject::SceneObject()
:camera(NULL) {
}

SceneObject::SceneObject(const SceneObject& orig) {
}

SceneObject::~SceneObject() {
}

void SceneObject::Render(){
    glLoadIdentity();
//    glMultMatrixf(transform.GetMatrix());
}

void SceneObject::SetCamera(Camera *camera){
    assert(this->camera==NULL); // only allow to set camera once
    this->camera = camera;
}
}
