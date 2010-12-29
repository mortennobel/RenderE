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
    PNGFileTextureDataSource();
    ~PNGFileTextureDataSource();
    TextureLoadStatus LoadTexture(char* name, int &outWidth, int &outHeight, TextureFormat &outFormat, unsigned char **outData);
    
private:
    PNGFileTextureDataSource(const PNGFileTextureDataSource& orig);
    
};
}
#endif	/* PNGTEXTUREDATASOURCE_H */

#endif // RENDER_E_PNG