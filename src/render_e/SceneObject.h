#ifndef SCENE_OBJECT_H
#define	SCENE_OBJECT_H

#include <vector>
#include "Transform.h"
#include "Component.h"
#include "MeshComponent.h"
#include "Material.h"
#include "Light.h"


namespace render_e {

// forward declaration
class Camera;

class SceneObject {
public:
    SceneObject();
    virtual ~SceneObject();
    const std::vector<Component*> * GetComponents() const;
    Transform *GetTransform();
    Camera *GetCamera();
    MeshComponent *GetMesh();
    void AddCompnent(Component* component);
    void RemoveComponent(Component* component);
    Material *GetMaterial();
    Light *GetLight();
    
    // Delegate call to transform object
    void AddChild(SceneObject *sceneObject);
    
    void SetName(std::string name) { this->name = name;}
    std::string GetName() {return name; }
private:
    SceneObject(const SceneObject& orig); // disallow copy constructor
    SceneObject& operator = (const SceneObject&); // disallow copy constructor
    
    Transform *transform;   
    Camera *camera;
    MeshComponent *mesh;
    Material *material;
    Light *light;
    std::vector<Component*> components;
    
    std::string name;
};
}

#endif	/* RENDEROBJECT_H */

