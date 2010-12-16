/*
 *  transform.cpp
 *  RenderE
 *
 *  Created by morten on 10/29/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Transform.h"
#include <iostream>
#include <cassert>

namespace render_e {

Transform::Transform(SceneObject *sceneObject)
:Component(TransformType),dirtyFlag(false), dirtyFlagInverse(false), 
        scale(1,1,1),parent(NULL),sceneObject(sceneObject)
{}

Transform::~Transform(void)
{}

void Transform::AddChild(Transform *transform){
    assert (transform->parent == NULL);
    transform->parent = this;
    children.push_back(transform);
}

bool Transform::RemoveChild(Transform *transform){
    using namespace std;
    assert(transform->parent == this);
    vector<Transform *>::iterator index = find (children.begin(), children.end(), transform);
    if (index != children.end()){
        // erase the 6th element
        children.erase (index);
        transform->parent = NULL;
    }
}

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

Matrix44 Transform::GetLocalTransform(){
    UpdateIfDirty();
    return localTransform;
}

Matrix44 Transform::GetLocalTransformInverse(){
    UpdateInverseIfDirty();
    return localTransformInverse;
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
    this->rotation.SetFromEuler(euler[0], euler[1], euler[2]);
    dirtyFlag = true;
    dirtyFlagInverse = true;
}

void Transform::SetScale(Vector3 &scale){
    this->scale = scale;
    dirtyFlag = true;
    dirtyFlagInverse = true;
}
}
