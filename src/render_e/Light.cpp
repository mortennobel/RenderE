/* 
 * File:   Light.cpp
 * Author: morten
 * 
 * Created on December 29, 2010, 6:23 PM
 */

#include "Light.h"

#include <cassert>
#include <GL/glew.h>
#include "SceneObject.h"

namespace render_e {

Light::Light() 
: Component(LightComponentType), lightType(PointLight), 
        constantAttenuation(1.0f), linearAttenuation(0.0f),
        quadraticAttenuation(0.0f), spotDirection(0,0,-1), spotCutoff(180) {
}

Light::Light(LightType lightType) 
: Component(LightComponentType), lightType(lightType), 
        constantAttenuation(1.0f), linearAttenuation(0.0f),
        quadraticAttenuation(0.0f), spotDirection(0,0,-1),spotCutoff(180) {
}

Light::~Light() {
}

void Light::SetupLight(int lightIndex){
    glEnable(GL_LIGHT0+lightIndex);
    // Setup and enable light 0
    glLightfv(GL_LIGHT0+lightIndex,GL_AMBIENT, GetAmbient().Get());
    glLightfv(GL_LIGHT0+lightIndex,GL_DIFFUSE, GetDiffuse().Get());
    glLightfv(GL_LIGHT0+lightIndex,GL_SPECULAR, GetSpecular().Get());
	glLighti(GL_LIGHT0+lightIndex, GL_SPOT_CUTOFF, spotCutoff); 
	glLightfv(GL_LIGHT0+lightIndex,GL_SPOT_DIRECTION, spotDirection.Get());
    float w = 0;
    if (GetLightType()==PointLight){
        w = 1;
    } else if (GetLightType()==DirectionalLight){
        w = 0;
    }
    SceneObject *sceneObject = GetOwner();
    assert(sceneObject != NULL);
    Vector4 lightPos(sceneObject->GetTransform()->GetPosition(), w);

    glLightfv(GL_LIGHT0+lightIndex,GL_POSITION, lightPos.Get());
}

}
