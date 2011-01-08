/* 
 * File:   ShaderDataSource.h
 * Author: morten
 *
 * Created on November 14, 2010, 10:07 PM
 */

#ifndef SHADERDATASOURCE_H
#define	SHADERDATASOURCE_H
#include <string>
#include "Shader.h"


namespace render_e {


class ShaderDataSource {
public:
    ShaderDataSource();
    virtual ~ShaderDataSource();
    
    Shader *LoadLinkShader(const char* name, ShaderLoadStatus &outStatus);
    
protected:
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

