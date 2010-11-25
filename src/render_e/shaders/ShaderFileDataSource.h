/* 
 * File:   ShaderFileDataSource.h
 * Author: morten
 *
 * Created on November 14, 2010, 10:12 PM
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
    
    ShaderLoadStatus LoadShaderSource(char* name, 
            char **vertexShaderData,
            char **fragmentShaderData);
private:

};
}

#endif	/* SHADERFILEDATASOURCE_H */

