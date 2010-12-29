/*
 *  Texture.cpp
 *  RenderE
 *
 *  Created by morten on 10/30/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Texture2D.h"

#include <cstdlib>
#include <cstring>
#include <cassert>
#include <GL/glew.h>

#include "TextureDataSource.h"


namespace render_e {

Texture2D::Texture2D(const char *resourceName)
:TextureBase(GL_TEXTURE_2D),textureDataSource(TextureDataSource::GetTextureDataSource()), interpolationLinear(true), clamp(false)
{
    assert(textureDataSource!=NULL);
    int length = strlen(resourceName);
    this->resourceName = new char[length];
    memcpy(this->resourceName,resourceName, length);
}

Texture2D::~Texture2D(){
    if (resourceName){
        delete[] resourceName;
    }
}
TextureLoadStatus Texture2D::Load(){    
    unsigned char* data = NULL;
    TextureLoadStatus res = textureDataSource->LoadTexture(resourceName, width, height, textureFormat, &data);
    if (res==OK){
        // allocate a texture name
        glGenTextures( 1, &textureId );
        // select our current texture
        glBindTexture( GL_TEXTURE_2D, textureId );
        
        // when texture area is small, bilinear filter the closest mipmap
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                 GL_LINEAR_MIPMAP_NEAREST );
        // when texture area is large, bilinear filter the original
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        
        // the texture wraps over at the edges (repeat)
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
        
        glPixelStorei(GL_UNPACK_ALIGNMENT,1);
        if (mipmapping){
            gluBuild2DMipmaps( GL_TEXTURE_2D, textureFormat==RGB?GL_RGB8:GL_RGBA8, width, height,
                   textureFormat==RGB?GL_RGB:GL_RGBA, GL_UNSIGNED_BYTE, data );
        } else {
            glTexImage2D(GL_TEXTURE_2D,0, textureFormat==RGB?GL_RGB8:GL_RGBA8, width, height, 
                    0, textureFormat==RGB?GL_RGB:GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
    }
    
    if (data!=NULL){
        free(data);
    }
    
    return res;
}
}

