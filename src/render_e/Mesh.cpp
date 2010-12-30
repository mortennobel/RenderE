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
        normals.push_back(Vector3(0,0,0));
    }
    
    for (int i=0;i<indices.size();i=i+3){
        int index1 = indices[i];
        int index2 = indices[i+1];
        int index3 = indices[i+2];
        Vector3 v1 = vertices[index1];
        Vector3 v2 = vertices[index2];
        Vector3 v3 = vertices[index3];
        
        Vector3 v1v2 = v2-v1;
        Vector3 v1v3 = v3-v1;
        
        Vector3 normal = v1v2.Cross(v1v3).Normalized();
        
        normals[index1] = normals[index1]+normal;
        normals[index2] = normals[index2]+normal;
        normals[index3] = normals[index3]+normal;
    }
    
    cout << "Normals are now:" << endl;
    for (int i=0;i<indices.size();i++){
        cout << normals[i][0]<<" "<< normals[i][1]<<" "<< normals[i][2]<<" "<<endl;
    }
    
    for (vector<Vector3>::iterator iter = normals.begin();iter != normals.end();iter++){
        (*iter).Normalize();
    }
    
    cout << "Normals are now:" << endl;
    for (int i=0;i<indices.size();i++){
        cout << normals[i][0]<<" "<< normals[i][1]<<" "<< normals[i][2]<<" "<<endl;
    }
}


void Mesh::SetVertices(Vector3 *vertices, int length){
    this->vertices.clear();
    for (int i=0;i<length;i++){
        this->vertices.push_back(vertices[i]);
    }
}

void Mesh::SetNormals(Vector3 *normals, int length){
    this->normals.clear();
    for (int i=0;i<length;i++){
        this->normals.push_back(normals[i]);
    }
}
void Mesh::SetTangents(Vector3 *tangents, int length){
    this->tangents.clear();
    for (int i=0;i<length;i++){
        this->tangents.push_back(tangents[i]);
    }
}

void Mesh::SetColors(Vector3 *colors, int length){
    this->colors.clear();
    for (int i=0;i<length;i++){
        this->colors.push_back(colors[i]);
    }

}
void Mesh::SetTextureCoords1(Vector2 *textureCoords1, int length){
    this->textureCoords1.clear();
    for (int i=0;i<length;i++){
        this->textureCoords1.push_back(textureCoords1[i]);
    }
}
void Mesh::SetTextureCoords2(Vector2 *textureCoords2, int length){
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
    
    for (vector<int>::iterator iter = indices.begin(); iter != indices.end();iter++){
        int val = *iter;
        if (val>=verticesSize){
            std::cerr<<"Invalid mesh index "<<val<<". Number of vertices defined: "<<verticesSize<<std::endl;
            return false;
        }
    }
    return true;
}
}
