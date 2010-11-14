/* 
 * File:   ShaderDataSource.h
 * Author: morten
 *
 * Created on November 14, 2010, 10:07 PM
 */

#ifndef SHADERDATASOURCE_H
#define	SHADERDATASOURCE_H

namespace render_e {

enum ShaderLoadStatus {
    FILE_NOT_FOUND,
    OK
};

class ShaderDataSource {
public:
    ShaderDataSource();
    virtual ~ShaderDataSource();
    
    virtual ShaderLoadStatus LoadLinkShader(char* name, int &size, unsigned char **data) = 0;
private:
    ShaderDataSource(const ShaderDataSource& orig); // disallow copy constructor
    ShaderDataSource& operator = (const ShaderDataSource&); // disallow copy constructor
    
};
}
#endif	/* SHADERDATASOURCE_H */

