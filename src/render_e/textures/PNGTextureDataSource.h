/* 
 * File:   PNGTextureDataSource.h
 * Author: morten
 *
 * Created on November 6, 2010, 11:07 AM
 */

#ifdef RENDER_E_PNG

#ifndef PNGTEXTUREDATASOURCE_H
#define	PNGTEXTUREDATASOURCE_H

#include "TextureDataSource.h"

namespace render_e {

class PNGTextureDataSource : public TextureDataSource {
public:
    PNGTextureDataSource();
    PNGTextureDataSource(const PNGTextureDataSource& orig);
    virtual ~PNGTextureDataSource();
    
    TextureLoadStatus LoadTexture(char* name, int &outWidth, int &outHeight, TextureFormat &outFormat, unsigned char **outData);
private:

};
}
#endif	/* PNGTEXTUREDATASOURCE_H */

#endif // RENDER_E_PNG