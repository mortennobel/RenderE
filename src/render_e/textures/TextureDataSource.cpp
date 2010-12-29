#include "TextureDataSource.h"

#include <cstring>
#include "PNGFileTextureDataSource.h"

namespace render_e {

#ifndef RENDER_E_NO_PNG
    TextureDataSource *TextureDataSource::textureDataSource = new PNGFileTextureDataSource();
#else
    TextureDataSource *TextureDataSource::textureDataSource = NULL;

#endif        
    
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
