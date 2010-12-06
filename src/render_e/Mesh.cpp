/* 
 * File:   Mesh.cpp
 * Author: morten
 * 
 * Created on December 6, 2010, 11:05 AM
 */

#include "Mesh.h"

#include <iostream>

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

int *Mesh::GetTriangles(){
    if (triangles.size()==0){
        return NULL;
    }
    return &triangles[0];
}

int Mesh::GetTriangleCount(){
    return triangles.size();
}

void Mesh::ComputeNormals(){
    // compute the normal for each face
    
    normals.clear();
    // fill normal vector
    while (normals.size()<vertices.size()){
        normals.push_back(Vector3());
    }
    
    for (int i=0;i<triangles.size();i=i+3){
        Vector3 v1 = vertices[triangles[i]];
        Vector3 v2 = vertices[triangles[i+1]];
        Vector3 v3 = vertices[triangles[i+2]];
        
        Vector3 v1v2 = v2-v1;
        Vector3 v1v3 = v3-v1;
        
        Vector3 normal = v1v2.Cross(v1v3).Normalized();
        
        // faceNormals[i] = normal;
        // todo allow shared normals
        normals[triangles[i]] = normal;
        normals[triangles[i+1]] = normal;
        normals[triangles[i+2]] = normal;
        
    }
}
}
