/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#ifndef CUBETEXTURE_H
#define	CUBETEXTURE_H

#include <string>

#include "TextureBase.h"
#include "TextureDataSource.h"

namespace render_e {
class CubeTexture : public TextureBase{
public:
    CubeTexture(const char* left, const char* right, const char* top, const char* bottom, const char* back, const char* front);
    virtual ~CubeTexture();
    virtual TextureLoadStatus Load();
    virtual void Create(int width, int height, TextureFormat textureFormat);
private:
    CubeTexture(const CubeTexture& orig); // disallow copy constructor
    CubeTexture& operator = (const CubeTexture&); // disallow copy constructor
    
    TextureDataSource *textureDataSource;
    std::string resourceNames[6];
};

}

#endif	/* CUBETEXTURE_H */

