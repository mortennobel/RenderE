/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
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
