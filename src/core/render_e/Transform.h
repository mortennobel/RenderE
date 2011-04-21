/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#ifndef RENDER_E_TRANSFORM_H
#define	RENDER_E_TRANSFORM_H

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Component.h"

namespace render_e {

/// This component contains information about spartial position, rotation and scale
/// It both contains the local transform and the global transform (where parents 
/// are taken into account).
/// This way Transform objects also is used to keep a transforms-hierarchy.
class Transform : public Component {
public:
    explicit Transform();
    
    ~Transform(void);
    
    glm::mat4 GetLocalTransform();
    glm::mat4 GetLocalTransformInverse();
    
    glm::mat4 GetGlobalTransform();
    glm::mat4 GetGlobalTransformInverse();
    
    glm::vec3 GetPosition() const;
    glm::vec3 GetScale() const;
    glm::quat GetRotation() const;
    void SetPosition(const glm::vec3 &newPosition);
    void SetRotation(const glm::quat &quaternion);
    void SetRotation(const glm::vec3 &euler);
    void SetScale(const glm::vec3 &scale);
    
    /// Returns the parent object to this transform (or NULL is not defined)
    Transform *GetParent();
    /// Sets the parent object to this object (and add this object to the parents child list)
    /// Use NULL to delete the current parent
    void SetParent(Transform *parent);
    
    /// Add the transform object as a child (and set the transforms parent object to this)
    void AddChild(Transform *transform);
    
    /// Removes the transform object from this objects child and set the parent of the transform object to NULL
    bool RemoveChild(Transform *transform);
    
    /// Returns the current children of the transform
    const std::vector<Transform *> *GetChildren() const;
private:
    Transform(const Transform& orig); // disallow copy constructor
    Transform& operator = (const Transform&); // disallow copy constructor
    
    void UpdateIfDirty();
    void UpdateInverseIfDirty();
    void UpdateGlobalIfDirty();
    void UpdateGlobalInverseIfDirty();
    

    /// Set the global dirty recursively
    void SetGlobalDirtyFlag();
    
    /// Set the global dirty flag on children and set local dirty
    void SetLocalDirty();
    
    /// The reason to use dirty flags is to postpone the matrix calculations as 
    /// long as possible. This way a few calculations should be avoided
    bool dirtyFlag;
    bool dirtyFlagInverse;
    bool dirtyFlagGlobal;
    bool dirtyFlagGlobalInverse;
    
    glm::vec3 position;
    glm::vec3 scale;
    glm::quat rotation;
    glm::mat4 localTransform;
    glm::mat4 localTransformInverse;
    glm::mat4 globalTransform;
    glm::mat4 globalTransformInverse;
    
    std::vector<Transform *> children;
    Transform *parent;
};
}

#endif