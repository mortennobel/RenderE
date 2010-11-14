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

class PNGFileTextureDataSource : public TextureDataSource {
public:
    static PNGFileTextureDataSource* Instance() {
        if (!s_instance) {
            s_instance = new PNGFileTextureDataSource();
        }
        return s_instance;
    }
    
    TextureLoadStatus LoadTexture(char* name, int &outWidth, int &outHeight, TextureFormat &outFormat, unsigned char **outData);
private:
    static PNGFileTextureDataSource *s_instance;
    PNGFileTextureDataSource();
    PNGFileTextureDataSource(const PNGFileTextureDataSource& orig);
    virtual ~PNGFileTextureDataSource();
};
}
#endif	/* PNGTEXTUREDATASOURCE_H */

#endif // RENDER_E_PNG