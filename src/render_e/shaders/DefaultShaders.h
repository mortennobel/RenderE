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
private:
    static DefaultShaders *s_instance;
    DefaultShaders();
    DefaultShaders(const DefaultShaders& orig);
    Shader *zOnly;
};
}
#endif	/* DEFAULTSHADERS_H */

