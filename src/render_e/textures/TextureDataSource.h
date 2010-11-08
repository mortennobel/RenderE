/*
 *  TextureDataSource.h
 *  RenderE
 *
 *  Created by morten on 10/30/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef TEXTURE_DATA_SOURCE_H
#define	TEXTURE_DATA_SOURCE_H

namespace render_e {

enum TextureLoadStatus{
    ERROR,
    ERROR_READING_FILE,
    INVALID_FORMAT,
    OK
};

enum TextureFormat {
    RGB,
    RGBA
};

class TextureDataSource {
public:    
    TextureDataSource();
    virtual ~TextureDataSource();
    
    virtual TextureLoadStatus LoadTexture(char* name, int &outWidth, int &outHeight, TextureFormat &outFormat, unsigned char **outData) = 0;
private:
};
}

#endif // TEXTURE_DATA_SOURCE_H
