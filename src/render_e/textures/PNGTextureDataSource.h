/* 
 * File:   PNGTextureDataSource.h
 * Author: morten
 *
 * Created on November 6, 2010, 11:07 AM
 */

#ifndef RENDER_E_NO_PNG

#ifndef PNGTEXTUREDATASOURCE_H
#define	PNGTEXTUREDATASOURCE_H

#include "TextureBase.h"
#include "TextureDataSource.h"

namespace render_e {

class PNGTextureDataSource : public TextureDataSource {
public:
    static PNGTextureDataSource* Instance() {
        if (!s_instance) {
            s_instance = new PNGTextureDataSource();
        }
        return s_instance;
    }
    
    TextureLoadStatus LoadTexture(char* name, int &outWidth, int &outHeight, TextureFormat &outFormat, unsigned char **outData);
private:
    static PNGTextureDataSource *s_instance;
    PNGTextureDataSource();
    PNGTextureDataSource(const PNGTextureDataSource& orig);
    virtual ~PNGTextureDataSource();
};
}
#endif	/* PNGTEXTUREDATASOURCE_H */

#endif // RENDER_E_PNG