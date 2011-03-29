/*
 *  transform.h
 *  RenderE
 *
 *  Created by morten on 10/29/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef RENDER_E_TRANSFORM_H
#define	RENDER_E_TRANSFORM_H

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Component.h"

namespace render_e {
    
class Transform : public Component {
public:
    explicit Transform();
    
    ~Transform(void);
    
    glm::mat4 GetLocalTransform();
    glm::mat4 GetLocalTransformInverse();

    glm::vec3 GetPosition() const;
    glm::vec3 GetScale() const;
    glm::quat GetRotation() const;
    void SetPosition(const glm::vec3 &newPosition);
    void SetRotation(const glm::quat &quaternion);
    void SetRotation(const glm::vec3 &euler);
    void SetScale(const glm::vec3 &scale);
    
    void AddChild(Transform *transform);
    bool RemoveChild(Transform *transform);
    std::vector<Transform *> *GetChildren(){return &children;}
    
private:
    Transform(const Transform& orig); // disallow copy constructor
    Transform& operator = (const Transform&); // disallow copy constructor
    
    void UpdateIfDirty();
    void UpdateInverseIfDirty();
    bool dirtyFlag;
    bool dirtyFlagInverse;
    glm::vec3 position;
    glm::vec3 scale;
    glm::quat rotation;
    glm::mat4 localTransform;
    glm::mat4 localTransformInverse;
    
    std::vector<Transform *> children;
    Transform *parent;
};
}

#endif