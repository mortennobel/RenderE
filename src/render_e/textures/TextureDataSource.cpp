#include "TextureDataSource.h"

#include <cstring>
#include "PNGFileTextureDataSource.h"

namespace render_e {

#ifndef RENDER_E_NO_PNG
    PNGFileTextureDataSource *pngInstance = PNGFileTextureDataSource::Instance();
#endif        
TextureDataSource *TextureDataSource::textureDataSource = pngInstance;
    
TextureDataSource::TextureDataSource(){
}

TextureDataSource::~TextureDataSource(){
}

TextureDataSource *TextureDataSource::GetTextureDataSource(){
    return textureDataSource;
}

void TextureDataSource::SetTextureDataSource(TextureDataSource *newTextureDataSource){
    textureDataSource = newTextureDataSource;
}

}
