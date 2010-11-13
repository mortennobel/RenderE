/* 
 * File:   RenderObject.h
 * Author: morten
 *
 * Created on October 31, 2010, 2:42 PM
 */

#ifndef RENDEROBJECT_H
#define	RENDEROBJECT_H

#include <vector>
#include "Transform.h"
#include "Component.h"
#include "Mesh.h"


namespace render_e {

// forward declaration
class Camera;

class SceneObject {
public:
    SceneObject();
    virtual ~SceneObject();
    void Render();
    const std::vector<Component*> * GetComponents() const;
    Transform &GetTransform() { return transform; }
    Camera *GetCamera() { return camera; }
    void AddCompnent(Component* component);
private:
    SceneObject(const SceneObject& orig); // disallow copy constructor
    SceneObject& operator = (const SceneObject&); // disallow copy constructor
    
    Transform transform;   
    Camera *camera;
    Mesh *mesh;
    std::vector<Component*> components;
};
}

#endif	/* RENDEROBJECT_H */

