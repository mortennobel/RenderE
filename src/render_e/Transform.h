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

#include "math/Vector3.h"
#include "math/Quaternion.h"
#include "math/Matrix44.h"
#include "Component.h"

namespace render_e {
    
class Transform : public Component {
public:
    explicit Transform(SceneObject *sceneObject);
    
    ~Transform(void);
    
    Matrix44 GetLocalTransform();
    Matrix44 GetLocalTransformInverse();

    Vector3 GetPosition() const;
    Vector3 GetScale() const;
    Quaternion GetRotation() const;
    void SetPosition(Vector3 &newPosition);
    void SetRotation(Quaternion &quaternion);
    void SetRotation(Vector3 &euler);
    void SetScale(Vector3 &scale);
    
    void AddChild(Transform *transform);
    bool RemoveChild(Transform *transform);
    std::vector<Transform *> *GetChildren(){return &children;}
    
    SceneObject *GetSceneObject(){return sceneObject;}
private:
    SceneObject *sceneObject;
    Transform(const Transform& orig); // disallow copy constructor
    Transform& operator = (const Transform&); // disallow copy constructor
    
    void UpdateIfDirty();
    void UpdateInverseIfDirty();
    bool dirtyFlag;
    bool dirtyFlagInverse;
    Vector3 position;
    Vector3 scale;
    Quaternion rotation;
    Matrix44 localTransform;
    Matrix44 localTransformInverse;
    
    std::vector<Transform *> children;
    Transform *parent;
};
}

#endif