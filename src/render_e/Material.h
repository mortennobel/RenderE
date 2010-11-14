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

using std::vector;

namespace render_e {
class Material : public Component{
public:
    Material(Shader *shader);
    Material(const Material& orig);
    virtual ~Material();
private:
    Shader *shader;
    vector<TextureBase*> textures;
};
}
#endif	/* MATERIAL_H */

