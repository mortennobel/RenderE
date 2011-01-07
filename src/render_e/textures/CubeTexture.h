/* 
 * File:   CubeTexture.h
 * Author: morten
 *
 * Created on November 11, 2010, 10:27 PM
 */

#ifndef CUBETEXTURE_H
#define	CUBETEXTURE_H

#include <string>

#include "TextureBase.h"
#include "TextureDataSource.h"

namespace render_e {
class CubeTexture : public TextureBase{
public:
    CubeTexture(const char* left, const char* right, const char* top, const char* bottom, const char* back, const char* front);
    virtual ~CubeTexture();
    virtual TextureLoadStatus Load();
private:
    CubeTexture(const CubeTexture& orig); // disallow copy constructor
    CubeTexture& operator = (const CubeTexture&); // disallow copy constructor
    
    TextureDataSource *textureDataSource;
    std::string resourceNames[6];
};

}

#endif	/* CUBETEXTURE_H */

