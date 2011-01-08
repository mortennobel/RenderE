/* 
 * File:   Light.h
 * Author: morten
 *
 * Created on December 29, 2010, 6:23 PM
 */

#ifndef LIGHT_H
#define	LIGHT_H

#include "Component.h"
#include "math/Vector4.h"

namespace render_e {

enum LightType{
    PointLight,
    DirectionalLight
};

class Light : public Component {
public:
    Light();
    Light(LightType lightType);
    virtual ~Light();
    Vector4 GetAmbient() { return ambient; }
    void SetAmbient(Vector4 ambient) { this->ambient = ambient; }
    Vector4 GetDiffuse() { return diffuse; }
    void SetDiffuse(Vector4 diffuse) { this->diffuse = diffuse; }
    Vector4 GetSpecular() { return specular; }
    void SetSpecular(Vector4 specular) { this->specular = specular; }
    float GetConstantAttenuation(){ return constantAttenuation; }
    void SetConstantAttenuation(float constantAttenuation) { this->constantAttenuation = constantAttenuation; }
    float GetLinearAttenuation() { return linearAttenuation; }
    void SetLinearAttenuation(float linearAttenuation) { this->linearAttenuation = linearAttenuation; }
    float GetQuadraticAttenuation() { return quadraticAttenuation; }
    void SetQuadraticAttenuation(float quadraticAttenuation) { this->quadraticAttenuation = quadraticAttenuation;}
    LightType GetLightType() { return lightType; }
    void SetLightType(LightType lightType) { this->lightType = lightType; }
    void SetupLight(int lightIndex);
private:
    LightType lightType;
    Vector4 ambient;
    Vector4 diffuse;
    Vector4 specular;
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
};

}

#endif	/* LIGHT_H */

