/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#ifndef SHADERDATASOURCE_H
#define	SHADERDATASOURCE_H
#include <string>
#include "Shader.h"


namespace render_e {


class ShaderDataSource {
public:
    ShaderDataSource(){}
    virtual ~ShaderDataSource(){}
    virtual ShaderLoadStatus LoadSharedSource(std::string &sharedVertexData, std::string &sharedFragmentData) = 0;
    virtual ShaderLoadStatus LoadShaderSource(const char* name, 
            std::string &vertexShaderData,
            std::string &fragmentShaderData) = 0;
private:
    ShaderDataSource(const ShaderDataSource& orig);  // disallow copy constructor
    ShaderDataSource& operator = (const ShaderDataSource&); // disallow copy constructor
    
};
}
#endif	/* SHADERDATASOURCE_H */

