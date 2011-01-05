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
#include <iostream>
#include <GL/glew.h>

#include "TextureDataSource.h"

using namespace std;

namespace render_e {

Texture2D::Texture2D()
: TextureBase(GL_TEXTURE_2D), textureDataSource(NULL), interpolationLinear(true), clamp(false), resourceName(NULL) {
    mipmapping = false;
}

Texture2D::Texture2D(const char *resourceName)
: TextureBase(GL_TEXTURE_2D), textureDataSource(TextureDataSource::GetTextureDataSource()), interpolationLinear(true), clamp(false) {
    assert(textureDataSource != NULL);
    int length = strlen(resourceName);
    this->resourceName = new char[length];
    memcpy(this->resourceName, resourceName, length);
}

Texture2D::~Texture2D() {
    if (resourceName) {
        delete[] resourceName;
    }
}

void Texture2D::GetTextureFormat( GLenum &format ) {
    switch (textureFormat) {
        case DEPTH:
            internalFormat = GL_DEPTH_COMPONENT;
            format = GL_LUMINANCE;
            break;
        case RGB:
            internalFormat = GL_RGB8;
            format = GL_RGB;
            break;
        case RGBA:
        default:
            internalFormat = GL_RGBA8;
            format = GL_RGBA;
            break;
    }
}

TextureLoadStatus Texture2D::Load() {
    unsigned char* data = NULL;
    TextureLoadStatus res = textureDataSource->LoadTexture(resourceName, width, height, textureFormat, &data);
    if (res == OK) {
        // allocate a texture name
        glGenTextures(1, &textureId);
        // select our current texture
        glBindTexture(GL_TEXTURE_2D, textureId);

        // when texture area is small, bilinear filter the closest mipmap
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                GL_LINEAR_MIPMAP_NEAREST);
        // when texture area is large, bilinear filter the original
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // the texture wraps over at the edges (repeat)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, clamp?GL_CLAMP:GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, clamp?GL_CLAMP:GL_REPEAT);

        GLenum format;

        GetTextureFormat(format);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        if (mipmapping) {
            gluBuild2DMipmaps(GL_TEXTURE_2D, internalFormat, width, height,
                    format, GL_UNSIGNED_BYTE, data);
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height,
                    0, format, GL_UNSIGNED_BYTE, data);
        }
    }

    if (data != NULL) {
        free(data);
    }

    return res;
}

void Texture2D::Create(int width, int height, TextureFormat textureFormat) {
    assert(!mipmapping); // mipmapping not supported
    this->width = width;
    this->height = height;
    // allocate a texture name
    glGenTextures(1, &textureId);
    cout << name << " Created textureid " << textureId << endl;
    // select our current texture
    glBindTexture(GL_TEXTURE_2D, textureId);

    // when texture area is small, bilinear filter the closest mipmap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            GL_LINEAR_MIPMAP_NEAREST);
    // when texture area is large, bilinear filter the original
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // the texture wraps over at the edges (repeat)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, clamp?GL_CLAMP:GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, clamp?GL_CLAMP:GL_REPEAT);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    
    GLenum format;

    GetTextureFormat(format);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height,
            0, format, GL_UNSIGNED_BYTE, NULL);

}

}

