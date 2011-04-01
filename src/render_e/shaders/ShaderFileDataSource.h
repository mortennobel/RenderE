/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#ifndef SHADERFILEDATASOURCE_H
#define	SHADERFILEDATASOURCE_H

#include "ShaderDataSource.h"

namespace render_e {
class ShaderFileDataSource : public ShaderDataSource {
public:
    ShaderFileDataSource();
    ShaderFileDataSource(const ShaderFileDataSource& orig);
    virtual ~ShaderFileDataSource();
protected:
    ShaderLoadStatus LoadSharedSource(std::string &sharedVertexData, std::string &sharedFragmentData);
    ShaderLoadStatus LoadShaderSource(const char* name, 
            std::string &vertexShaderData,
            std::string &fragmentShaderData);
private:

};
}

#endif	/* SHADERFILEDATASOURCE_H */

