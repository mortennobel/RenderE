/* 
 * File:   Mesh.cpp
 * Author: morten
 * 
 * Created on November 12, 2010, 8:51 PM
 */

#include "MeshComponent.h"

#include <cassert>
#include <cstring>
#include <GL/glew.h>

// todo - remove this - for debugging purpose only
#include <iostream>
#ifdef _WIN32
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#define BUFFER_OFFSET(bytes) ((GLubyte*) NULL + (bytes))

namespace render_e {
MeshComponent::MeshComponent()
:Component(MeshType), vboName(0),triangles(NULL){
}

MeshComponent::~MeshComponent() {
    Release();
}

void MeshComponent::Render(){
    if (vboName != 0){
        // bind buffer (set active)
        glBindBuffer(GL_ARRAY_BUFFER, vboName);
        // vertex pointer to buffer
        glVertexPointer(3, GL_FLOAT, 0,0);
        if (normalOffset != -1){
            // normal pointer to buffer
            glNormalPointer(GL_FLOAT, 0, (GLubyte*)normalOffset);
        }
        if (texture1Offset != -1){
            // texcoord pointer to buffer
            glTexCoordPointer(2, GL_FLOAT, 0, (GLubyte*)texture1Offset);
        }
        
        glDrawArrays(GL_TRIANGLES, triangles[0], triangleCount);
    } else {
        std::cout << "Mesh not initialized" << std::endl;
    }
}

void MeshComponent::SetMesh(Mesh *mesh){
    this->mesh = mesh;
    Vector3 *vertices = mesh->GetVertices();
    Vector3 *normals = mesh->GetNormals();
    Vector3 *tangent = mesh->GetTangents();
    Vector2 *textureCoords = mesh->GetTextureCoords1();
    Vector2 *textureCoords2 = mesh->GetTextureCoords2();
    int primitiveCount = mesh->GetPrimitiveCount();
    triangles = mesh->GetTriangles();
    triangleCount = mesh->GetTriangleCount();
    if (vboName!=0){
        Release();
    }
    this->verticeCount = primitiveCount;
    unsigned int buffersize = sizeof(float)*(3+3+2)*primitiveCount;
    // create temp buffer
	float *buffer = new float[buffersize];
    // copy data to tmp buffer
	// data is organized [vertices, normals, texCoords, textCoords2]
	memcpy(buffer,vertices,sizeof(float)*3*primitiveCount);
	memcpy(buffer+3*primitiveCount,normals,sizeof(float)*3*primitiveCount);
	memcpy(buffer+2*3*primitiveCount,textureCoords,sizeof(float)*2*primitiveCount);
    
    unsigned int vertexBufferSize = sizeof(float)*3*primitiveCount;
    
    
    glGenBuffers(1,&vboName);
    // Bind buffer (set buffer active)
	glBindBuffer(GL_ARRAY_BUFFER, vboName); // bind
	// copy data to buffer
	glBufferData(GL_ARRAY_BUFFER, buffersize, buffer,GL_STATIC_DRAW);
    
}

void MeshComponent::Release(){
    if (vboName != 0){
        glDeleteBuffers(1, &vboName);
        vboName = 0;
    }
}

}
