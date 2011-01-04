/* 
 * File:   Material.h
 * Author: morten
 *
 * Created on November 14, 2010, 10:50 PM
 */

#ifndef MATERIAL_H
#define	MATERIAL_H

#include <vector>
#include <string>
#include "shaders/Shader.h"
#include "textures/TextureBase.h"
#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Vector4.h"
#include "Component.h"

namespace render_e {

enum ShaderParamType{
    SPT_FLOAT,
    SPT_VECTOR2,
    SPT_VECTOR3,
    SPT_VECTOR4,
    SPT_INT,
    SPT_TEXTURE
};

struct ShaderParameters{
    int id;
    ShaderParamType paramType;
    union ShaderValue {
        float f[4];
        int integer[2]; // value, bind texturetype
    } shaderValue;
};

class Material : public Component{
public:
    Material(Shader *shader);
    virtual ~Material();
    void Bind();
    
    bool SetVector2(std::string name, Vector2 vec);
    bool SetVector3(std::string name, Vector3 vec);
    bool SetVector4(std::string name, Vector4 vec);
    bool SetFloat(std::string name, float f);
    bool SetTexture(std::string name, TextureBase *texture);
    bool SetInt(std::string name, int i);
    
    void SetName(std::string name) { this->name = name;}
    std::string GetName() {return name; }
private:
    Material(const Material& orig); // disallow copy constructor
    Material& operator = (const Material&); // disallow copy constructor
    
    void AddParameter(ShaderParameters &param);
    
    Shader *shader;
    std::vector<TextureBase*> textures;    
    std::string name;
    std::vector<ShaderParameters> parameters;
};
}
#endif	/* MATERIAL_H */

