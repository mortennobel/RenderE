/* 
 * File:   Light.h
 * Author: morten
 *
 * Created on December 29, 2010, 6:23 PM
 */

#ifndef LIGHT_H
#define	LIGHT_H

#include "Component.h"
#include "math/Vector3.h"

namespace render_e {

enum LightType{
    PointLight
};

class Light : public Component {
public:
    Light();
    Light(LightType lightType);
    virtual ~Light();
    Vector3 GetAmbient() { return ambient; }
    void SetAmbient(Vector3 ambient) { this->ambient = ambient; }
    Vector3 GetDiffuse() { return diffuse; }
    void SetDiffuse(Vector3 diffuse) { this->diffuse = diffuse; }
    Vector3 GetSpecular() { return specular; }
    void SetSpecular(Vector3 specular) { this->specular = specular; }
    float GetConstantAttenuation(){ return constantAttenuation; }
    void SetConstantAttenuation() { this->constantAttenuation = constantAttenuation; }
    float GetLinearAttenuation() { return linearAttenuation; }
    void SetLinearAttenuation(float linearAttenuation) { this->linearAttenuation = linearAttenuation; }
    float GetQuadraticAttenuation() { return quadraticAttenuation; }
    void SetQuadraticAttenuation(float quadraticAttenuation) { this->quadraticAttenuation = quadraticAttenuation;}
    LightType GetLightType() { return lightType; }
    void SetLightType(LightType lightType) { this->lightType = lightType; }
private:
    LightType lightType;
    Vector3 ambient;
    Vector3 diffuse;
    Vector3 specular;
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
};

}

#endif	/* LIGHT_H */

