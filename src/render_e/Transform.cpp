/*
 *  transform.cpp
 *  RenderE
 *
 *  Created by morten on 10/29/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Transform.h"

namespace render_e {

Transform::Transform(void)
:dirtyFlag(false), dirtyFlagInverse(false)
{}
Transform::Transform(const Transform& t)
:dirtyFlag(t.dirtyFlag), dirtyFlagInverse(t.dirtyFlagInverse), rotation(t.rotation),
        position(t.position), localTransform(t.localTransform), localTransformInverse(t.localTransformInverse)
{}

Transform::~Transform(void)
{}

void Transform::UpdateIfDirty(){
    if (dirtyFlag){
        rotation.GetMatrix(&localTransform);
        localTransform = Matrix44::Scale(scale)*Matrix44::Translate(position)*localTransform; // todo is this the right order???
        dirtyFlag = false;
    }
}

void Transform::UpdateInverseIfDirty(){
    if (dirtyFlagInverse){
        rotation.GetMatrix(&localTransformInverse);
        localTransformInverse = localTransformInverse.Transpose()*Matrix44::Translate(-position)*Matrix44::ScaleInverse(scale); // todo is this in right order?
        dirtyFlagInverse = false;
    }
}

float *Transform::GetLocalTransform(){
    UpdateIfDirty();
    return localTransform.GetReference();
}


Vector3 Transform::GetPosition() const {
    
}

Quaternion Transform::GetRotation() const {
    
}

Vector3  Transform::GetScale() const{
    return scale;
}

void Transform::SetPosition(Vector3 &newPosition) {
    position = newPosition;
    dirtyFlag = true;
}

void Transform::SetRotation(Quaternion &quaternion) {

}

void Transform::SetRotation(Vector3 &euler){
    this->rotation = Quaternion();
}

void Transform::SetScale(Vector3 &scale){
    this->scale = scale;
}
}
