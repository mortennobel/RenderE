/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
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
        dirtyFlagGlobal(false),dirtyFlagGlobalInverse(false),
        scale(1,1,1),parent(NULL), rotation(glm::quat(0.0f,0.0f,0.0f,0.0f))
{
}

Transform::~Transform(void)
{}

Transform *Transform::GetParent(){
    return parent;
}

void Transform::SetParent(Transform *parent){
    // remove current parent
    if (this->parent != NULL){
        bool res = this->parent->RemoveChild(this);
        assert(res); // if not true, then something serious is wrong with parent-child relationship
    }
    // delegate to parent
    parent->AddChild(this);
}

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
        children.erase (index);
        transform->parent = NULL;
		return true;
    }
	return false;
}

const std::vector<Transform *> *Transform::GetChildren() const {
    return &children;
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

void Transform::UpdateGlobalIfDirty(){
    if (dirtyFlagGlobal && parent != NULL){
        parent->UpdateGlobalIfDirty();
        globalTransform = GetLocalTransform()*parent->GetGlobalTransform();
        dirtyFlagGlobal = false;
    }
}

void Transform::UpdateGlobalInverseIfDirty(){
    if (dirtyFlagGlobalInverse && parent != NULL){
        parent->UpdateGlobalInverseIfDirty();
        globalTransformInverse = GetLocalTransformInverse()*parent->GetGlobalTransformInverse();
        dirtyFlagGlobalInverse = false;
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

glm::mat4 Transform::GetGlobalTransform(){
    if (parent==NULL){
        return GetLocalTransform();
    }
    UpdateGlobalIfDirty();
    return globalTransform;
}

glm::mat4 Transform::GetGlobalTransformInverse(){
    if (parent==NULL){
        return GetLocalTransformInverse();
    }
    UpdateGlobalInverseIfDirty();
    return globalTransformInverse;
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

void Transform::SetGlobalDirtyFlag(){
    dirtyFlagGlobal = true;
    dirtyFlagGlobalInverse = true;
    std::vector<Transform *>::iterator iter = children.begin();
    for (;iter != children.end();iter++){
        (*iter)->SetGlobalDirtyFlag();
    }
}

void Transform::SetLocalDirty(){
    dirtyFlag = true;
    dirtyFlagInverse = true;
    SetGlobalDirtyFlag();
}

void Transform::SetPosition(const glm::vec3 &newPosition) {
    position = newPosition;
    SetLocalDirty();
}

void Transform::SetRotation(const glm::quat &quaternion) {
    this->rotation = quaternion;
    SetLocalDirty();
}

void Transform::SetRotation(const glm::vec3 &euler){
    Mathf::SetFromEuler(euler[0], euler[1], euler[2], this->rotation);
    SetLocalDirty();
}

void Transform::SetScale(const glm::vec3 &scale){
    this->scale = scale;
    SetLocalDirty();
}
}
