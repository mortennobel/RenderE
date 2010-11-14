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
:Component(TransformType),dirtyFlag(false), dirtyFlagInverse(false), scale(1,1,1)
{}

Transform::~Transform(void)
{}

void Transform::UpdateIfDirty(){
    if (dirtyFlag){
        rotation.GetMatrix(&localTransform);
        localTransform = Matrix44::Scale(scale)* Matrix44::Translate(position) *localTransform;
        dirtyFlag = false;
    }
}

void Transform::UpdateInverseIfDirty(){
    if (dirtyFlagInverse){
        rotation.GetMatrix(&localTransformInverse);
        localTransformInverse = localTransformInverse.Transpose()* Matrix44::Translate(-position) * Matrix44::ScaleInverse(scale);
        dirtyFlagInverse = false;
    }
}

float *Transform::GetLocalTransform(){
    UpdateIfDirty();
    return localTransform.GetReference();
}

float *Transform::GetLocalTransformInverse(){
    UpdateInverseIfDirty();
    return localTransformInverse.GetReference();
}


Vector3 Transform::GetPosition() const {
    return position;
}

Quaternion Transform::GetRotation() const {
    return rotation;
}

Vector3  Transform::GetScale() const{
    return scale;
}

void Transform::SetPosition(Vector3 &newPosition) {
    position = newPosition;
    dirtyFlag = true;
    dirtyFlagInverse = true;
}

void Transform::SetRotation(Quaternion &quaternion) {
    this->rotation = quaternion;
    dirtyFlag = true;
    dirtyFlagInverse = true;
}

void Transform::SetRotation(Vector3 &euler){
    this->rotation = Quaternion();
    dirtyFlag = true;
    dirtyFlagInverse = true;
}

void Transform::SetScale(Vector3 &scale){
    this->scale = scale;
    dirtyFlag = true;
    dirtyFlagInverse = true;
}
}
