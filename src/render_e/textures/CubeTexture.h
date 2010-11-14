/* 
 * File:   CubeTexture.h
 * Author: morten
 *
 * Created on November 11, 2010, 10:27 PM
 */

#ifndef CUBETEXTURE_H
#define	CUBETEXTURE_H

#include "TextureBase.h"
#include "TextureDataSource.h"

namespace render_e {
class CubeTexture : TextureBase{
public:
    CubeTexture(char* left, char* right, char* top, char* bottom, char* back, char* front);
    virtual ~CubeTexture();
    virtual TextureLoadStatus Load();
private:
    CubeTexture(const CubeTexture& orig); // disallow copy constructor
    CubeTexture& operator = (const CubeTexture&); // disallow copy constructor
    
    TextureDataSource *textureDataSource;
    char** resourceNames;
};

}

#endif	/* CUBETEXTURE_H */

