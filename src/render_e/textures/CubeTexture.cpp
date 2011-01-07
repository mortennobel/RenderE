/* 
 * File:   CubeTexture.cpp
 * Author: morten
 * 
 * Created on November 11, 2010, 10:27 PM
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
    resourceNames[2].append(top);
    resourceNames[3].append(bottom);
    resourceNames[4].append(back);
    resourceNames[5].append(front);
}

CubeTexture::~CubeTexture() {
}

TextureLoadStatus CubeTexture::Load(){
    // allocate a texture name
    glGenTextures( 1, &textureId );
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    
    for (int i=0;i<6;i++){
        int width;
        int height;
        TextureFormat textureFormat;
        unsigned char *data = NULL;
        TextureLoadStatus res = textureDataSource->LoadTexture(resourceNames[i].c_str(), width, height, textureFormat, &data);
        
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
