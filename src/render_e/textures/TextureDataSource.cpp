/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

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
