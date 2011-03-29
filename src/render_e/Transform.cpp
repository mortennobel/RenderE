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
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "math/Mathf.h"

namespace render_e {

Transform::Transform()
:Component(TransformType),dirtyFlag(false), dirtyFlagInverse(false), 
        scale(1,1,1),parent(NULL)
{
}

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
		return true;
    }
	return false;
}

void Transform::UpdateIfDirty(){
    if (dirtyFlag){
        localTransform = glm::gtc::quaternion::mat4_cast(rotation);
        glm::mat4 translateMatrix;
        glm::gtc::matrix_transform::translate(translateMatrix,position);
        glm::mat4 scaleMatrix;
        glm::gtc::matrix_transform::scale(translateMatrix,scale);
        localTransform = translateMatrix * scaleMatrix * localTransform;
        dirtyFlag = false;
    }
}

void Transform::UpdateInverseIfDirty(){
    if (dirtyFlagInverse){
        glm::mat4 inverseRotation = glm::transpose(glm::gtc::quaternion::mat4_cast(rotation));
        glm::mat4 inverseScaleMatrix;
        glm::gtc::matrix_transform::scale(inverseScaleMatrix,1.0f / scale);
        glm::mat4 inverseTranslateMatrix;
        glm::gtc::matrix_transform::translate(inverseTranslateMatrix,-position);
        
        localTransformInverse = inverseRotation * inverseScaleMatrix * inverseTranslateMatrix;
        dirtyFlagInverse = false;
    }
}

glm::mat4 Transform::GetLocalTransform(){
    UpdateIfDirty();
    return localTransform;
}

glm::mat4 Transform::GetLocalTransformInverse(){
    UpdateInverseIfDirty();
    return localTransformInverse;
}

glm::vec3 Transform::GetPosition() const {
    return position;
}

glm::quat Transform::GetRotation() const {
    return rotation;
}

glm::vec3  Transform::GetScale() const{
    return scale;
}

void Transform::SetPosition(const glm::vec3 &newPosition) {
    position = newPosition;
    dirtyFlag = true;
    dirtyFlagInverse = true;
}

void Transform::SetRotation(const glm::quat &quaternion) {
    this->rotation = quaternion;
    dirtyFlag = true;
    dirtyFlagInverse = true;
}

void Transform::SetRotation(const glm::vec3 &euler){
    Mathf::SetFromEuler(euler[0], euler[1], euler[2], this->rotation);
    dirtyFlag = true;
    dirtyFlagInverse = true;
}

void Transform::SetScale(const glm::vec3 &scale){
    this->scale = scale;
    dirtyFlag = true;
    dirtyFlagInverse = true;
}
}
