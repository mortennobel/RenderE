/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#include "Mesh.h"

#include <sstream>
#include <limits>
#include <glm/glm.hpp>
#include "Log.h"

using namespace std;

namespace render_e {
Mesh::Mesh() {
}

Mesh::Mesh(const Mesh& orig) {
}

Mesh::~Mesh() {
}

glm::vec3 *Mesh::GetVertices(){
    if (vertices.size()==0){
        return NULL;
    }
    return &vertices[0];
}

glm::vec3 *Mesh::GetNormals(){
    if (normals.size()==0){
        return NULL;
    }
    return &normals[0];
}

glm::vec3 *Mesh::GetTangents(){
    if (tangents.size()==0){
        return NULL;
    }
    return &tangents[0];
}

glm::vec3 *Mesh::GetColors(){
    if (colors.size()==0){
        return NULL;
    }
    return &colors[0];
}

glm::vec2 *Mesh::GetTextureCoords1(){
    if (textureCoords1.size()==0){
        return NULL;
    }
    return &textureCoords1[0];
}

glm::vec2 *Mesh::GetTextureCoords2(){
    if (textureCoords2.size()==0){
        return NULL;
    }
    return &textureCoords2[0];
}

int Mesh::GetPrimitiveCount(){
    return vertices.size();
}

int *Mesh::GetIndices(){
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
        normals.push_back(glm::vec3(0,0,0));
    }
    
    for (int i=0;i<indices.size();i=i+3){
        int index1 = indices[i];
        int index2 = indices[i+1];
        int index3 = indices[i+2];
        glm::vec3 v1 = vertices[index1];
        glm::vec3 v2 = vertices[index2];
        glm::vec3 v3 = vertices[index3];
        
        glm::vec3 v1v2 = v2-v1;
        glm::vec3 v1v3 = v3-v1;
        
        glm::vec3 normal = glm::normalize(glm::cross(v1v2,v1v3));
        
        normals[index1] = normals[index1]+normal;
        normals[index2] = normals[index2]+normal;
        normals[index3] = normals[index3]+normal;
    }
    
    for (vector<glm::vec3>::iterator iter = normals.begin();iter != normals.end();iter++){
        (*iter) = glm::normalize(*iter);
    }
}


void Mesh::SetVertices(glm::vec3 *vertices, int length){
    this->vertices.clear();
    for (int i=0;i<length;i++){
        this->vertices.push_back(vertices[i]);
    }
}

void Mesh::SetNormals(glm::vec3 *normals, int length){
    this->normals.clear();
    for (int i=0;i<length;i++){
        this->normals.push_back(normals[i]);
    }
}
void Mesh::SetTangents(glm::vec3 *tangents, int length){
    this->tangents.clear();
    for (int i=0;i<length;i++){
        this->tangents.push_back(tangents[i]);
    }
}

void Mesh::SetColors(glm::vec3 *colors, int length){
    this->colors.clear();
    for (int i=0;i<length;i++){
        this->colors.push_back(colors[i]);
    }

}
void Mesh::SetTextureCoords1(glm::vec2 *textureCoords1, int length){
    this->textureCoords1.clear();
    for (int i=0;i<length;i++){
        this->textureCoords1.push_back(textureCoords1[i]);
    }
}
void Mesh::SetTextureCoords2(glm::vec2 *textureCoords2, int length){
    this->textureCoords2.clear();
    for (int i=0;i<length;i++){
        this->textureCoords2.push_back(textureCoords2[i]);
    }
}
void Mesh::SetIndices(int *indices, int length){
    this->indices.clear();
    for (int i=0;i<length;i++){
        this->indices.push_back(indices[i]);
    }
}

bool Mesh::IsValid(){
    int verticesSize = vertices.size();
    if (verticesSize==0){
        return false;
    }
    if (normals.size()>0 && normals.size() != verticesSize){
        std::stringstream ss;
        ss<<"Invalid size of normals was "<<normals.size()<<" should be "<<verticesSize;
        ERROR(ss.str());
        return false;
    }
    if (tangents.size()>0 && tangents.size() != verticesSize){
        std::stringstream ss;
        ss<<"Invalid size of tangents was "<<tangents.size()<<" should be "<<verticesSize;
        ERROR(ss.str());
        return false;
    }
    if (colors.size()>0 && colors.size() != verticesSize){
        std::stringstream ss;
        ss<<"Invalid size of colors was "<<colors.size()<<" should be "<<verticesSize;
        ERROR(ss.str());
        return false;
    }
    if (textureCoords1.size()>0 && textureCoords1.size() != verticesSize){
        std::stringstream ss;
        ss<<"Invalid size of textureCoords1 was "<<textureCoords1.size()<<" should be "<<verticesSize;
        ERROR(ss.str());
        return false;
    }
    if (textureCoords2.size()>0 && textureCoords2.size() != verticesSize){
        std::stringstream ss;
        ss<<"Invalid size of textureCoords2 was "<<textureCoords2.size()<<" should be "<<verticesSize;
        ERROR(ss.str());
        return false;
    }
    
    for (vector<int>::iterator iter = indices.begin(); iter != indices.end();iter++){
        int val = *iter;
        if (val>=verticesSize){
            std::stringstream ss;
            ss<<"Invalid mesh index "<<val<<". Number of vertices defined: "<<verticesSize;
            ERROR(ss.str());
            return false;
        }
    }
    return true;
}
}
