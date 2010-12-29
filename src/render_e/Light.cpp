/* 
 * File:   Light.cpp
 * Author: morten
 * 
 * Created on December 29, 2010, 6:23 PM
 */

#include "Light.h"

namespace render_e {

Light::Light() 
: Component(LightComponentType), lightType(PointLight), 
        constantAttenuation(1.0f), linearAttenuation(0.0f),
        quadraticAttenuation(0.0f){
}

Light::Light(LightType lightType) 
: Component(LightComponentType), lightType(lightType), 
        constantAttenuation(1.0f), linearAttenuation(0.0f),
        quadraticAttenuation(0.0f){
}

Light::~Light() {
}

}
