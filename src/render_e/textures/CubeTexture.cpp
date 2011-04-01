/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#include "CubeTexture.h"
#include <cstring>
#include <cassert>
#include <iostream>
#include "GL/glew.h"


namespace render_e {

CubeTexture::CubeTexture(
        const char* left, const char* right, 
        const char* top, const char* bottom, 
        const char* back, const char* front)
:TextureBase(GL_TEXTURE_CUBE_MAP), textureDataSource(TextureDataSource::GetTextureDataSource()){
    assert(textureDataSource!=NULL);
    resourceNames[0].append(left);
    resourceNames[1].append(right);
    resourceNames[2].append(bottom);
    resourceNames[3].append(top);
    resourceNames[4].append(back);
    resourceNames[5].append(front);
}

CubeTexture::~CubeTexture() {
}

void CubeTexture::Create(int width, int height, TextureFormat textureFormat){
    // http://stackoverflow.com/questions/462721/rendering-to-cube-map
    this->width = width;
    this->height = height;
    if (textureFormat == RGB || textureFormat == RGBA){
        // color cube map
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        for (int face = 0; face < 6; face++) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, 0, GL_RGBA,
                width, height, 0, GL_RGBA, GL_FLOAT, NULL);
        }
    } else if (textureFormat == DEPTH){
        // depth cube map
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        for (int face = 0; face < 6; face++) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, 0, GL_DEPTH_COMPONENT24,
                width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        }
    } else {
        std::cout << "Unsupported texture format in CubeTexture::Create. Was "<<
                textureFormat<<std::endl;
    }
}

TextureLoadStatus CubeTexture::Load(){
    // allocate a texture name
    glGenTextures( 1, &textureId );
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    
    for (int i=0;i<6;i++){
        TextureFormat textureFormat;
        unsigned char *data = NULL;
		unsigned int w,h;
        TextureLoadStatus res = textureDataSource->LoadTexture(resourceNames[i].c_str(), w, h, textureFormat, &data);
        width = w;
		height = h;
        if (res != OK){
            std::cout<<"Error loading "<<resourceNames[i]<<std::endl;
            return res;
        }
        
        glPixelStorei(GL_UNPACK_ALIGNMENT,1);
        if (mipmapping){
            gluBuild2DMipmaps( GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, textureFormat==RGB?GL_RGB8:GL_RGBA8, width, height,
                   textureFormat==RGB?GL_RGB:GL_RGBA, GL_UNSIGNED_BYTE, data );
        } else {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,0, textureFormat==RGB?GL_RGB8:GL_RGBA8, width, height, 
                    0, textureFormat==RGB?GL_RGB:GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        
        if (data!=NULL){
           delete []data;
        }
        if (res!=OK){
            return res;
        }
    }
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    
    return OK;
}
}
