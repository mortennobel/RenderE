/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#include "ShaderFileDataSource.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

namespace render_e {
ShaderFileDataSource::ShaderFileDataSource() {
}

ShaderFileDataSource::ShaderFileDataSource(const ShaderFileDataSource& orig) {
}

ShaderFileDataSource::~ShaderFileDataSource() {
}

ShaderLoadStatus ShaderFileDataSource::LoadSharedSource(std::string &sharedVertexData, std::string &sharedFragmentData){
    using namespace std;
    
    const char *fileEndings[2] = {".vs", ".fs"};
    string *sources[2] = {&sharedVertexData,&sharedFragmentData};
    for (int i=0;i<2;i++){
        string filename("shader-src/shared");
        filename = filename.append(fileEndings[i]);
        ifstream input(filename.c_str());
        
        stringstream oss;
        oss << input.rdbuf();
        *(sources[i]) = oss.str();
        input.close();
        
        if (input.fail()) {
            // file did not exist or error during read
            std::cout<<"Cannot load "<<filename<<std::endl;
            return SHADER_FILE_NOT_FOUND;
        }
    }
    return SHADER_OK;
}

ShaderLoadStatus ShaderFileDataSource::LoadShaderSource(const char* name, 
            std::string &vertexShaderData,
            std::string &fragmentShaderData){
    using namespace std;
    
    const char *fileEndings[2] = {".vs", ".fs"};
    string *sources[2] = {&vertexShaderData,&fragmentShaderData};
    for (int i=0;i<2;i++){
        string filename("shader-src/");
        filename = filename.append(name);
        filename = filename.append(fileEndings[i]);
        ifstream input(filename.c_str());
        
        stringstream oss;
        oss << input.rdbuf();
        *(sources[i]) = oss.str();
        input.close();
        
        if (input.fail()) {
            // file did not exist or error during read
            std::cout<<"Cannot load "<<filename<<std::endl;
            return SHADER_FILE_NOT_FOUND;
        }
    }
    return SHADER_OK;
}
}
