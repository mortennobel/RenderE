/* 
 * File:   Material.h
 * Author: morten
 *
 * Created on November 14, 2010, 10:50 PM
 */

#ifndef MATERIAL_H
#define	MATERIAL_H

#include <vector>
#include "shaders/Shader.h"
#include "textures/TextureBase.h"
#include "Component.h"

namespace render_e {
class Material : public Component{
public:
    Material(Shader *shader);
    virtual ~Material();
    void Bind();
private:
    Material(const Material& orig); // disallow copy constructor
    Material& operator = (const Material&); // disallow copy constructor
    
    Shader *shader;
    std::vector<TextureBase*> textures;
};
}
#endif	/* MATERIAL_H */

