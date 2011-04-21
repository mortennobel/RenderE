/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#ifndef COMPONENT_H
#define	COMPONENT_H

#include <string>

namespace render_e {

// forward declaration
class SceneObject;

// Todo should be a bit-vector indicating the type instead
enum ComponentType{
    TransformType,
    MeshType,
    CameraType,
    MaterialType,
    LightComponentType,
    ParticleSystemType,
    CustomType
};

class Component {
public:
    Component(ComponentType componentType);
    virtual ~Component();
    SceneObject *GetOwner();
    void SetOwner(SceneObject *owner);
    ComponentType GetComponentType (){ return componentType; }
    /// Only enabled components receive events and is rendered
    bool IsEnabled(){ return enabled; }
    /// Only enabled components receive events and is rendered
    void SetEnabled(bool enabledNew){ enabled = enabledNew; }
    
    // Updates each component before every frame
    virtual void Update() {}
    
    /// Get the component class name
    virtual const char* GetComponentName() const;
private:
    Component(const Component& orig); // disallow copy constructor
    Component& operator = (const Component&); // disallow copy constructor
    
    SceneObject *owner;
    ComponentType componentType;
    
    bool enabled;
};

}
#endif	/* COMPONENT_H */

