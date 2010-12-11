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
:Component(MeshType), vboName(0),vboElements(0)
#ifdef RENDER_E_NO_VBO
,indicesCount(0),buffer(NULL)
#endif
{
}

MeshComponent::~MeshComponent() {
    Release();
}

void MeshComponent::Render(){
    if (indicesCount==0){
        return;
        std::cout << "Mesh not initialized" << std::endl;
    }
#ifdef RENDER_E_NO_VBO    
    glVertexPointer(3, GL_FLOAT, stride, buffer);
    if (normalOffset != -1){
        glNormalPointer(GL_FLOAT, stride, buffer+normalOffset);
    }
    if (texture1Offset != -1){
        glTexCoordPointer(2, GL_FLOAT, stride, buffer+texture1Offset);
    }
    if (colorOffset != -1){
        glColorPointer(3, GL_FLOAT, stride, buffer+colorOffset);
    }
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_SHORT, indices);
#else 
    if (vboName != 0){
        // bind buffer (set active)
        glBindBuffer(GL_ARRAY_BUFFER, vboName);
        
        // bind buffer (set active)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboElements);
        // vertex pointer to buffer
        glVertexPointer(3, GL_FLOAT, stride,BUFFER_OFFSET(0));
        if (normalOffset != -1){
            // normal pointer to buffer
            glNormalPointer(GL_FLOAT, stride, BUFFER_OFFSET(normalOffset));
        }
        if (texture1Offset != -1){
            // texcoord pointer to buffer
            glTexCoordPointer(2, GL_FLOAT, stride, BUFFER_OFFSET(texture1Offset));
        }
        
        if (colorOffset != -1){
            glColorPointer(3, GL_FLOAT, stride, BUFFER_OFFSET(colorOffset));
        }
        
        glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_SHORT, 0 );
    }
#endif //RENDER_E_NO_VBO
}

void MeshComponent::SetMesh(Mesh *mesh){
    assert (mesh->GetVertices() != NULL);
    assert (mesh->IsValid());
    Vector3 *vertices = mesh->GetVertices();
    Vector3 *normals = mesh->GetNormals();
    Vector3 *tangents = mesh->GetTangents();
    Vector3 *colors = mesh->GetColors();
    Vector2 *textureCoords = mesh->GetTextureCoords1();
    Vector2 *textureCoords2 = mesh->GetTextureCoords2();
    int primitiveCount = mesh->GetPrimitiveCount();
    unsigned short *indices = mesh->GetIndices(); // todo rename
    indicesCount = mesh->GetIndicesCount();
    Release();
    
    // Calculate size of data
    stride = 0;
    int sizePrimitives = sizeof(float)*3;
    int offset = sizePrimitives; // vertices
    if (normals != NULL){
        normalOffset = offset;
        offset += sizePrimitives;
        stride += sizeof(float)*3;
    } else {
        normalOffset = -1;
    }
    
    if (tangents != NULL){
        tangentOffset = offset;
        offset += sizePrimitives;
        stride += sizeof(float)*3;
    } else {
        tangentOffset = -1;
    }
    
    if (colors != NULL){
        colorOffset = offset;
        offset += sizePrimitives;
        stride += sizeof(float)*3;
    } else {
        colorOffset = -1;
    }
    int sizeTexCoords = sizeof(float)*2;
    if (textureCoords != NULL) {
        texture1Offset = offset;
        offset += sizeTexCoords;
        stride += sizeof(float)*2;
    } else {
        texture1Offset = -1;
    }
    if (textureCoords2 != NULL) {
        texture2Offset = offset;
        offset += sizeTexCoords;
        stride += sizeof(float)*2;
    } else {
        texture2Offset = -1;
    }
    
    // create temp buffer
    unsigned int buffersize = offset*primitiveCount;
#ifndef RENDER_E_NO_VBO    
	unsigned char *buffer;
#else
    this->indices = new unsigned short[indicesCount];
    memcpy(this->indices, indices, indicesCount*sizeof(unsigned short));
#endif
    buffer = new unsigned char[buffersize];
    float *bufferAsFloat = (float *)buffer;
    
    // Memory layout: Vertex0, Normal0, ..., Vertex1, Normal1, ...
    // This layout gives a better performance, since the data that belongs
    // together are located close to each other
    int destIndex = 0;
    for (int i=0;i<primitiveCount;i++){
        memcpy(&bufferAsFloat[destIndex], &vertices[i], sizePrimitives);
        destIndex += 3;
        if (normals != NULL){
            memcpy(&bufferAsFloat[destIndex], &normals[i], sizePrimitives);
            destIndex += 3;
        }
        if (tangents != NULL){
            memcpy(&bufferAsFloat[destIndex], &tangents[i], sizePrimitives);
            destIndex += 3;
        }
        if (textureCoords != NULL){
            memcpy(&bufferAsFloat[destIndex], &textureCoords[i], sizeTexCoords);
            destIndex += 2;
        }
        if (textureCoords2 != NULL){
            memcpy(&bufferAsFloat[destIndex], &textureCoords2[i], sizeTexCoords);
            destIndex += 2;
        }
    }
#ifndef RENDER_E_NO_VBO
    unsigned int buffernames[2];
    glGenBuffers(2,buffernames);
    vboName = buffernames[0];
    vboElements = buffernames[1];
    // Bind buffer (set buffer active)
	glBindBuffer(GL_ARRAY_BUFFER, vboName); // bind
	// copy data to buffer
	glBufferData(GL_ARRAY_BUFFER, buffersize, buffer,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // bind
    
    // Bind buffer (set buffer active)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboElements); // bind
    // copy data to buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount*sizeof(unsigned short), indices,GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // bind
#endif
    
}

void MeshComponent::Release(){
#ifdef RENDER_E_NO_VBO    
	if (buffer != NULL){
        delete []buffer;
        delete []indices;
        buffer = NULL;
        indices = NULL;
    }
#else
    if (vboName != 0){
        glDeleteBuffers(1, &vboName);
        vboName = 0;
    }
#endif
}

}
