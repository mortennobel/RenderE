#include "TextureDataSource.h"

#include <cstring>
#include "PNGFileTextureDataSource.h"

namespace render_e {

#ifndef RENDER_E_NO_PNG
    PNGFileTextureDataSource *pngInstance = PNGFileTextureDataSource::Instance();
    TextureDataSource *TextureDataSource::textureDataSource = pngInstance;
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
