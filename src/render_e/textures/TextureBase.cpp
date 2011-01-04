/* 
 * File:   TextureBase.cpp
 * Author: morten
 * 
 * Created on November 12, 2010, 11:50 AM
 */

#include "TextureBase.h"
#include <GL/glew.h>

namespace render_e {

TextureBase::TextureBase(int textureType)
:textureType(textureType), mipmapping(true), textureId(0){
}

TextureBase::TextureBase(const TextureBase& orig) {
}

TextureBase::~TextureBase() {
    Unload();
}

void TextureBase::Bind(){
    glBindTexture(textureType, textureId );
}
void TextureBase::Unbind(){
    glBindTexture(textureType , 0 );
}
void TextureBase::Unload(){
    if (textureId!=0){
        Unbind();
        glDeleteTextures(1, &textureId);
        textureId = 0;
    }
}
}
