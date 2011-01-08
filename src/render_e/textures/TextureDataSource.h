/*
 *  Abstract class for texture builders
 */


#ifndef TEXTURE_DATA_SOURCE_H
#define	TEXTURE_DATA_SOURCE_H

#include "TextureBase.h"

namespace render_e {



class TextureDataSource {
public:    
    TextureDataSource();
    virtual ~TextureDataSource();
    
    virtual TextureLoadStatus LoadTexture(const char* name, int &outWidth, int &outHeight, TextureFormat &outFormat, unsigned char **outData) = 0;
    static TextureDataSource *GetTextureDataSource();
    static void SetTextureDataSource(TextureDataSource *textureDataSource);
private:
    TextureDataSource(const TextureDataSource& orig); // disallow copy constructor
    TextureDataSource& operator = (const TextureDataSource&); // disallow copy constructor
    
    static TextureDataSource *textureDataSource;
};
}

#endif // TEXTURE_DATA_SOURCE_H
