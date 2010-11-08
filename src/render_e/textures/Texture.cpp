/*
 *  Texture.cpp
 *  RenderE
 *
 *  Created by morten on 10/30/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Texture.h"
#include "TextureDataSource.h"

namespace render_e {

Texture::Texture(TextureDataSource *textureDataSource)
:textureDataSource(textureDataSource)
{}

Texture::Texture(const Texture& orig)
:textureDataSource(orig.textureDataSource)
{}


Texture::~Texture(){

}
void Texture::Load(){
}
void Texture::Bind(){
}
void Texture::Unbind(){
}
void Texture::Unload(){
}
}

