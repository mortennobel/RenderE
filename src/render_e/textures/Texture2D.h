/*
 *  Texture.h
 *  RenderE
 *
 *  Created by morten on 10/30/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TEXTURE_H
#define	TEXTURE_H

#include "TextureBase.h"
#include "TextureDataSource.h"

namespace render_e {

class Texture2D : public TextureBase {
public:
    Texture2D(const char *resourceName);
    virtual ~Texture2D();
    virtual TextureLoadStatus Load();
private:
    Texture2D(const Texture2D& orig); // disallow copy constructor
    Texture2D& operator = (const Texture2D&); // disallow copy constructor
    TextureDataSource *textureDataSource;
    bool interpolationLinear;
    bool clamp;
    char *resourceName;
    int width;
    int height;
    TextureFormat textureFormat;
};
}
#endif // TEXTURE_H
