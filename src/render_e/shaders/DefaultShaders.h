/* 
 * File:   DefaultShaders.h
 * Author: morten
 *
 * Created on November 26, 2010, 3:49 PM
 */

#ifndef DEFAULTSHADERS_H
#define	DEFAULTSHADERS_H
#include "Shader.h"

namespace render_e {
class DefaultShaders {
public:
    virtual ~DefaultShaders();
    /**
     * Singleton pattern
     * @return the render base instance
     */
    static DefaultShaders* Instance() {
        if (!s_instance) {
            s_instance = new DefaultShaders();
        }
        return s_instance;
    }
    
    Shader *GetZOnly();
    Shader *GetDiffuseColor();
    Shader *GetDiffuseTexture();
private:
    static DefaultShaders *s_instance;
    DefaultShaders();
    DefaultShaders(const DefaultShaders& orig);
    Shader *zOnly;
    Shader *diffuseColor;
    Shader *diffuseTexture;
};
}
#endif	/* DEFAULTSHADERS_H */

