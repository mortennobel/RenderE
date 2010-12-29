/* 
 * File:   Component.h
 * Author: morten
 *
 * Created on November 8, 2010, 10:32 PM
 */

#ifndef COMPONENT_H
#define	COMPONENT_H

#include <string>

namespace render_e {

// forward declaration
class SceneObject;

enum ComponentType{
    TransformType,
    MeshType,
    CameraType,
    MaterialType,
    LightComponentType,
    CustomType
};

class Component {
public:
    Component(ComponentType componentType);
    virtual ~Component();
    SceneObject *GetOwner();
    void SetOwner(SceneObject *owner);
    ComponentType GetComponentType (){ return componentType; }
    void SetName(std::string name) { this->name = name;}
    std::string GetName() {return name; }
private:
    Component(const Component& orig); // disallow copy constructor
    Component& operator = (const Component&); // disallow copy constructor
    
    SceneObject *owner;
    ComponentType componentType;
    std::string name;
};

}
#endif	/* COMPONENT_H */

