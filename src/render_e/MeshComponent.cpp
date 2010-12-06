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
:Component(MeshType), vboName(0){
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
        
    } else {
        std::cout << "Mesh not initialized" << std::endl;
    }

}

void MeshComponent::InitMesh(Vector3 *vertices, Vector3 *normals, Vector3 *tangent,
        Vector2 *textureCoords, Vector2 *textureCoords2, int verticeCount, 
        int *triangles, int triangleCount){
    if (vboName!=0){
        Release();
    }
    this->verticeCount = verticeCount;
    unsigned int buffersize = sizeof(float)*(3+3+2)*verticeCount;
    // create temp buffer
	float *buffer = new float[buffersize];
    // copy data to tmp buffer
	// data is organized [vertices, normals, texCoords, textCoords2]
	memcpy(buffer,vertices,sizeof(float)*3*verticeCount);
	memcpy(buffer+3*verticeCount,normals,sizeof(float)*3*verticeCount);
	memcpy(buffer+2*3*verticeCount,textureCoords,sizeof(float)*2*verticeCount);
    
    unsigned int vertexBufferSize = sizeof(float)*3*verticeCount;
    
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
