/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#include "Light.h"

#include <cassert>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
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
    glLightfv(GL_LIGHT0+lightIndex,GL_AMBIENT, glm::value_ptr(GetAmbient()));
    glLightfv(GL_LIGHT0+lightIndex,GL_DIFFUSE, glm::value_ptr(GetDiffuse()));
    glLightfv(GL_LIGHT0+lightIndex,GL_SPECULAR, glm::value_ptr(GetSpecular()));
	glLighti(GL_LIGHT0+lightIndex, GL_SPOT_CUTOFF, spotCutoff); 
	glLightfv(GL_LIGHT0+lightIndex,GL_SPOT_DIRECTION, glm::value_ptr(spotDirection));
    float w = 0;
    if (GetLightType()==PointLight){
        w = 1;
    } else if (GetLightType()==DirectionalLight){
        w = 0;
    }
    SceneObject *sceneObject = GetOwner();
    assert(sceneObject != NULL);
    glm::vec4 lightPos(sceneObject->GetTransform()->GetPosition(), w);

    glLightfv(GL_LIGHT0+lightIndex,GL_POSITION, glm::value_ptr(lightPos));
}

}
