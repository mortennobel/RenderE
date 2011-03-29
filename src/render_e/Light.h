/* 
 * File:   Light.h
 * Author: morten
 *
 * Created on December 29, 2010, 6:23 PM
 */

#ifndef LIGHT_H
#define	LIGHT_H

#include "Component.h"
#include <glm/glm.hpp>

namespace render_e {

enum LightType{
    PointLight,
    DirectionalLight,
	SpotLight
};

class Light : public Component {
public:
    Light();
    Light(LightType lightType);
    virtual ~Light();
    glm::vec4 GetAmbient() { return ambient; }
    void SetAmbient(glm::vec4 ambient) { this->ambient = ambient; }
    glm::vec4 GetDiffuse() { return diffuse; }
    void SetDiffuse(glm::vec4 diffuse) { this->diffuse = diffuse; }
    glm::vec4 GetSpecular() { return specular; }
    void SetSpecular(glm::vec4 specular) { this->specular = specular; }
    float GetConstantAttenuation(){ return constantAttenuation; }
    void SetConstantAttenuation(float constantAttenuation) { this->constantAttenuation = constantAttenuation; }
    float GetLinearAttenuation() { return linearAttenuation; }
    void SetLinearAttenuation(float linearAttenuation) { this->linearAttenuation = linearAttenuation; }
    float GetQuadraticAttenuation() { return quadraticAttenuation; }
    void SetQuadraticAttenuation(float quadraticAttenuation) { this->quadraticAttenuation = quadraticAttenuation;}
    LightType GetLightType() { return lightType; }
    void SetLightType(LightType lightType) { this->lightType = lightType; }
    void SetupLight(int lightIndex);
	glm::vec3 GetSpotDirection() { return spotDirection; }
	void SetSpotDirection(glm::vec3 &p) { spotDirection = p; }
	int GetSpotCutoff(){ return spotCutoff; }
	void SetSpotCutoff(int s) { spotCutoff = s; }
private:
    LightType lightType;
    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
	glm::vec3 spotDirection;
	int spotCutoff;
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
};

}

#endif	/* LIGHT_H */

