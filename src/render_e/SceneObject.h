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


namespace render_e {

// forward declaration
class Camera;

class SceneObject {
public:
    SceneObject();
    SceneObject(const SceneObject& orig);
    virtual ~SceneObject();
    void Render();
    Transform &GetTransform() { return transform; }
    Camera *GetCamera() { return camera; }
    void SetCamera(Camera *camera);
private:
     Transform transform;   
     Camera *camera;
     std::vector<Component*> components;
};
}

#endif	/* RENDEROBJECT_H */

