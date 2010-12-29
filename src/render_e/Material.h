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
class Material : public Component{
public:
    Material(Shader *shader);
    virtual ~Material();
    void Bind();
    
    void SetVector2(std::string name, Vector2 vec);
    void SetVector3(std::string name, Vector3 vec);
    void SetVector4(std::string name, Vector4 vec);
    void SetFloat(std::string name, float f);
    void SetTexture(std::string name, TextureBase *texture);
private:
    Material(const Material& orig); // disallow copy constructor
    Material& operator = (const Material&); // disallow copy constructor
    
    Shader *shader;
    std::vector<TextureBase*> textures;    
};
}
#endif	/* MATERIAL_H */

