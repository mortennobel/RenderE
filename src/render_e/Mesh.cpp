/* 
 * File:   Mesh.cpp
 * Author: morten
 * 
 * Created on December 6, 2010, 11:05 AM
 */

#include "Mesh.h"

#include <iostream>
#include <limits>

using namespace std;

namespace render_e {
Mesh::Mesh() {
}

Mesh::Mesh(const Mesh& orig) {
}

Mesh::~Mesh() {
}

Vector3 *Mesh::GetVertices(){
    if (vertices.size()==0){
        return NULL;
    }
    return &vertices[0];
}

Vector3 *Mesh::GetNormals(){
    if (normals.size()==0){
        return NULL;
    }
    return &normals[0];
}

Vector3 *Mesh::GetTangents(){
    if (tangents.size()==0){
        return NULL;
    }
    return &tangents[0];
}

Vector3 *Mesh::GetColors(){
    if (colors.size()==0){
        return NULL;
    }
    return &colors[0];
}

Vector2 *Mesh::GetTextureCoords1(){
    if (textureCoords1.size()==0){
        return NULL;
    }
    return &textureCoords1[0];
}

Vector2 *Mesh::GetTextureCoords2(){
    if (textureCoords2.size()==0){
        return NULL;
    }
    return &textureCoords2[0];
}

unsigned short Mesh::GetPrimitiveCount(){
    return vertices.size();
}

unsigned short *Mesh::GetIndices(){
    if (indices.size()==0){
        return NULL;
    }
    return &indices[0];
}

int Mesh::GetIndicesCount(){
    return indices.size();
}

void Mesh::ComputeNormals(){
    // compute the normal for each face
    
    normals.clear();
    // fill normal vector
    while (normals.size()<vertices.size()){
        normals.push_back(Vector3());
    }
    
    for (int i=0;i<indices.size();i=i+3){
        Vector3 v1 = vertices[indices[i]];
        Vector3 v2 = vertices[indices[i+1]];
        Vector3 v3 = vertices[indices[i+2]];
        
        Vector3 v1v2 = v2-v1;
        Vector3 v1v3 = v3-v1;
        
        Vector3 normal = v1v2.Cross(v1v3).Normalized();
        
        // faceNormals[i] = normal;
        // todo allow shared normals
        normals[indices[i]] = normal;
        normals[indices[i+1]] = normal;
        normals[indices[i+2]] = normal;
        
    }
}


void Mesh::SetVertices(Vector3 *vertices, int length){
    this->vertices.clear();
    for (;length>0;length--){
        this->vertices.push_back(*vertices);
        vertices++;
    }
}

void Mesh::SetNormals(Vector3 *normals, int length){
    this->normals.clear();
    for (;length>0;length--){
        this->normals.push_back(*normals);
        normals++;
    }
}
void Mesh::SetTangents(Vector3 *tangents, int length){
    this->tangents.clear();
    for (;length>0;length--){
        this->tangents.push_back(*tangents);
        tangents++;
    }
}

void Mesh::SetColors(Vector3 *colors, int length){
    this->colors.clear();
    for (;length>0;length--){
        this->colors.push_back(*colors);
        colors++;
    }

}
void Mesh::SetTextureCoords1(Vector2 *textureCoords1, int length){
    this->textureCoords1.clear();
    for (;length>0;length--){
        this->textureCoords1.push_back(*textureCoords1);
        textureCoords1++;
    }
}
void Mesh::SetTextureCoords2(Vector2 *textureCoords2, int length){
    this->textureCoords2.clear();
    for (;length>0;length--){
        this->textureCoords2.push_back(*textureCoords2);
        textureCoords2++;
    }
}
void Mesh::SetIndices(unsigned short *indices, int length){
    this->indices.clear();
    for (;length>0;length--){
        this->indices.push_back(*indices);
        indices++;
    }
}

bool Mesh::IsValid(){
    int verticesSize = vertices.size();
    if (verticesSize==0){
        return false;
    }
    if (normals.size()>0 && normals.size() != verticesSize){
        std::cerr<<"Invalid size of normals was "<<normals.size()<<" should be "<<verticesSize<<std::endl;
        return false;
    }
    if (tangents.size()>0 && tangents.size() != verticesSize){
        std::cerr<<"Invalid size of tangents was "<<tangents.size()<<" should be "<<verticesSize<<std::endl;
        return false;
    }
    if (colors.size()>0 && colors.size() != verticesSize){
        std::cerr<<"Invalid size of colors was "<<colors.size()<<" should be "<<verticesSize<<std::endl;
        return false;
    }
    if (textureCoords1.size()>0 && textureCoords1.size() != verticesSize){
        std::cerr<<"Invalid size of textureCoords1 was "<<textureCoords1.size()<<" should be "<<verticesSize<<std::endl;
        return false;
    }
    if (textureCoords2.size()>0 && textureCoords2.size() != verticesSize){
        std::cerr<<"Invalid size of textureCoords2 was "<<textureCoords2.size()<<" should be "<<verticesSize<<std::endl;
        return false;
    }
    
    if (verticesSize>USHRT_MAX){
        std::cerr<<"Invalid mesh size "<<verticesSize<<". Max supported size is:: "<<USHRT_MAX<<std::endl;
        return false;
    }
    for (vector<unsigned short>::iterator iter = indices.begin(); iter != indices.end();iter++){
        unsigned short val = *iter;
        if (val>=verticesSize){
            std::cerr<<"Invalid mesh index "<<val<<". Number of vertices defined: "<<verticesSize<<std::endl;
            return false;
        }
    }
    return true;
}
}
