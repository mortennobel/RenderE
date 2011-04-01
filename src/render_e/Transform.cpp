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
        scale(1,1,1),parent(NULL), rotation(glm::quat(0.0f,0.0f,0.0f,0.0f))
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
        // update localTransform to translate*scale*rotate
        localTransform = glm::mat4(
                glm::vec4(1,0,0,0),
                glm::vec4(0,1,0,0),
                glm::vec4(0,0,1,0),
                glm::vec4(position,1)
                );
        localTransform = glm::gtc::matrix_transform::scale(localTransform,scale);
        localTransform = localTransform * glm::gtc::quaternion::mat4_cast(rotation);
        dirtyFlag = false;
    }
}

void Transform::UpdateInverseIfDirty(){
    if (dirtyFlagInverse){
        // update localTransformInverse to rotate^-1*scale^1*translate^-1
        localTransformInverse = glm::transpose(glm::gtc::quaternion::mat4_cast(rotation));
        localTransformInverse = glm::gtc::matrix_transform::scale(localTransformInverse,1.0f / scale);
        localTransformInverse = glm::gtc::matrix_transform::translate(localTransformInverse,-position);
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
