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

#include "TextureDataSource.h"

namespace render_e {

class Texture {
public:
    Texture(TextureDataSource *textureDataSource);
    Texture(const Texture& orig);
    virtual ~Texture();
    void Load();
    void Bind();
    void Unbind();
    void Unload();
private:
    TextureDataSource *textureDataSource;
};
}
#endif // TEXTURE_H
