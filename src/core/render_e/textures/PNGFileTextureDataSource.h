/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#ifndef RENDER_E_NO_PNG

#ifndef PNGTEXTUREDATASOURCE_H
#define	PNGTEXTUREDATASOURCE_H

#include "TextureBase.h"
#include "TextureDataSource.h"

namespace render_e {

class PNGFileTextureDataSource : public TextureDataSource {
public:
    PNGFileTextureDataSource();
    ~PNGFileTextureDataSource();
    TextureLoadStatus LoadTexture(const char* name, unsigned int &outWidth, unsigned int &outHeight, TextureFormat &outFormat, unsigned char **outData);
    
private:
    PNGFileTextureDataSource(const PNGFileTextureDataSource& orig);
    
};
}
#endif	/* PNGTEXTUREDATASOURCE_H */

#endif // RENDER_E_PNG