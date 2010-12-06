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
#include "MeshComponent.h"
#include "Material.h"


namespace render_e {

// forward declaration
class Camera;

class SceneObject {
public:
    SceneObject();
    virtual ~SceneObject();
    const std::vector<Component*> * GetComponents() const;
    Transform &GetTransform();
    Camera *GetCamera();
    MeshComponent *GetMesh();
    void AddCompnent(Component* component);
    Material *GetMaterial();
private:
    SceneObject(const SceneObject& orig); // disallow copy constructor
    SceneObject& operator = (const SceneObject&); // disallow copy constructor
    
    Transform transform;   
    Camera *camera;
    MeshComponent *mesh;
    Material *material;
    std::vector<Component*> components;
};
}

#endif	/* RENDEROBJECT_H */

