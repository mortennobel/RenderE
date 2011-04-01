/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
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
    int length = strlen(resourceName)+1;
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
            internalFormat = GL_DEPTH_COMPONENT24;
            format = GL_DEPTH_COMPONENT;
			storageType = GL_FLOAT;
            break;
        case RGB:
            internalFormat = GL_RGB8;
            format = GL_RGB;
			storageType = GL_UNSIGNED_BYTE;
            break;
        case RGBA:
			internalFormat = GL_RGBA8;
            format = GL_RGBA;
			storageType = GL_UNSIGNED_BYTE;
            break;
        default:
            cout<<"Unexpected texture format"<<endl;
			internalFormat = GL_RGBA8;
            format = GL_RGBA;
			storageType = GL_UNSIGNED_BYTE;
			break;
    }
}

TextureLoadStatus Texture2D::Load() {
    unsigned char* data = NULL;
	unsigned int w;
	unsigned int h;
    TextureLoadStatus res = textureDataSource->LoadTexture(resourceName, w, h, textureFormat, &data);
	width = w;
	height = h;
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
		glBindTexture(GL_TEXTURE_2D, 0);
    }

    if (data != NULL) {
        free(data);
    }

    return res;
}

void Texture2D::Create(int width, int height, TextureFormat textureFormat) {
    this->width = width;
    this->height = height;
	this->textureFormat = textureFormat;
    // allocate a texture name
    glGenTextures(1, &textureId);
    // select our current texture
    glBindTexture(GL_TEXTURE_2D, textureId);

	if (textureFormat==DEPTH){
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
		// This is to allow usage of shadow2DProj function in the shader
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
		glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY); 				
	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	} else {
		// when texture area is small, bilinear filter the closest mipmap
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_LINEAR_MIPMAP_NEAREST);
		// when texture area is large, bilinear filter the original
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// the texture wraps over at the edges (repeat)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, clamp?GL_CLAMP:GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, clamp?GL_CLAMP:GL_REPEAT);

	}
    

    
	// glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	
	
    
    GLenum format;
    GetTextureFormat(format);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height,
            0, format, storageType, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
}

}

