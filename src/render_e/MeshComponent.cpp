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
#include <glm/gtc/type_ptr.hpp>

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

#ifdef RENDER_E_NO_VBO
void  MeshComponent::DebugRendering(){
    static int c = 0;
    if (c++>0){
        return;
    }
    using namespace std;
    cout<<"Print rendering start"<<endl;
    for (int i=0;i<indicesCount;i++){
        int index = ((unsigned char*)indices)[i];
        glm::vec3 *vv = (glm::vec3*)(&(buffer[index*stride]));
        glm::vec3 v = vv[0];
        cout<<index<<"  "<<v[0]<<","<<v[1]<<","<<v[2]<<endl;
        if (normalOffset!=-1){
            glm::vec3 n = vv[1];
            cout<<index<<"      "<<n[0]<<","<<n[1]<<","<<n[2]<<endl;
        }
    }
    cout<<"Print rendering start"<<endl;
}
#endif //RENDER_E_NO_VBO

void MeshComponent::Render(){
    if (indicesCount==0){
        return;
        std::cout << "Mesh not initialized" << std::endl;
    }
#ifdef RENDER_E_NO_VBO 
#ifdef RENDER_INTERMEDIATE_MODE
    glBegin(GL_TRIANGLES);
    
    for (int i=0;i<indicesCount;i++){
        
        int index;
        switch (indexType){
            case GL_UNSIGNED_BYTE:
                index = (static_cast<GLubyte*>(indices))[i];
                break;
            case GL_UNSIGNED_SHORT:
                index = (static_cast<GLushort*>(indices))[i];
                break;
            case GL_UNSIGNED_INT:
                index = (static_cast<GLuint*>(indices))[i];
                break;
        }
        
        glm::vec3 *vv = (glm::vec3*)(&(buffer[index*(stride)]));
        
        if (normalOffset!=-1){
            glNormal3fv(vv[1].Get());
        }
        
        if (texture1Offset != -1){
            using namespace std;
            Vector2 *vv = (Vector2*)(&(buffer[texture1Offset+index*(stride)]));
            glTexCoord2fv(vv->Get());
        }
        
        glVertex3fv(vv[0].Get());
        
    }
    
    glEnd();
#else
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
    glDrawElements(GL_TRIANGLES, indicesCount, indexType, indices);
#endif /* RENDER_INTERMEDIATE_MODE */
#else 
    if (vboName != 0){
        // bind buffer (set active)
        glBindBuffer(GL_ARRAY_BUFFER, vboName);
        
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
        // vertex pointer to buffer
        glVertexPointer(3, GL_FLOAT, stride,BUFFER_OFFSET(vertexOffset));
        // bind buffer (set active)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboElements);
        glDrawElements(GL_TRIANGLES, indicesCount, indexType, BUFFER_OFFSET(0) );
        
    }
#endif //RENDER_E_NO_VBO
}

void MeshComponent::SetMesh(Mesh *mesh){
    assert (mesh->GetVertices() != NULL);
    assert (mesh->IsValid());
    glm::vec3 *vertices = mesh->GetVertices();
    glm::vec3 *normals = mesh->GetNormals();
    glm::vec3 *tangents = mesh->GetTangents();
    glm::vec3 *colors = mesh->GetColors();
    glm::vec2 *textureCoords = mesh->GetTextureCoords1();
    glm::vec2 *textureCoords2 = mesh->GetTextureCoords2();
    int primitiveCount = mesh->GetPrimitiveCount();
    int *indices = mesh->GetIndices(); // todo rename
    indicesCount = mesh->GetIndicesCount();
    Release();
    
    // Calculate size of data
    
    int sizePrimitives = sizeof(glm::vec3);
    int offset = 0;
    if (normals != NULL){
        normalOffset = offset;
        offset += sizePrimitives;
    } else {
        normalOffset = -1;
    }
    
    if (tangents != NULL){
        tangentOffset = offset;
        offset += sizePrimitives;
    } else {
        tangentOffset = -1;
    }
    
    if (colors != NULL){
        colorOffset = offset;
        offset += sizePrimitives;
    } else {
        colorOffset = -1;
    }
    int sizeTexCoords = sizeof(glm::vec2);
    if (textureCoords != NULL) {
        texture1Offset = offset;
        offset += sizeTexCoords;
    } else {
        texture1Offset = -1;
    }
    if (textureCoords2 != NULL) {
        texture2Offset = offset;
        offset += sizeTexCoords;
    } else {
        texture2Offset = -1;
    }
    // vertices
    vertexOffset = offset;
    offset += sizePrimitives;
    stride = offset;
    
    // create temp buffer
    unsigned int buffersize = offset*primitiveCount*sizeof(float);
    
    void *indicesDest;
    int indicesSize;
    
    if (primitiveCount < 0xff){
        indicesSize = sizeof(unsigned char);
        this->indexType = GL_UNSIGNED_BYTE;
        GLubyte *byteBuffer = new GLubyte[indicesCount];
        for (int i=0;i<indicesCount;i++){
            byteBuffer[i] = static_cast<unsigned char>(indices[i]);
        }
        indicesDest = byteBuffer;
    } else if (primitiveCount < 0xffff){
        indicesSize = sizeof(unsigned short);
        this->indexType = GL_UNSIGNED_SHORT;
        GLushort *shortBuffer = new GLushort[indicesCount];
        for (int i=0;i<indicesCount;i++){
            shortBuffer[i] = static_cast<unsigned short>(indices[i]);
        }
        indicesDest = shortBuffer;
    } else {
        indicesSize = sizeof(int);
        this->indexType = GL_UNSIGNED_INT;
        GLuint *intBuffer = new GLuint[indicesCount];
        memcpy(intBuffer, indices, indicesCount*indicesSize);
        indicesDest = intBuffer;
    }
         
#ifndef RENDER_E_NO_VBO    
	unsigned char *buffer;
#else
    this->indices = indicesDest;
#endif
    buffer = new unsigned char[buffersize];
    
    // Memory layout: Normal0, ..., Vertex0,  Normal1, ..., Vertex1, ...
    // This layout gives a better performance, since the data that belongs
    // together are located close to each other
    
    int destIndex = 0;
    for (int i=0;i<primitiveCount;i++){
        if (normals != NULL){
            memcpy(&(buffer[destIndex*sizeof(float)]), glm::value_ptr(normals[i]), sizePrimitives);
            destIndex += 3;
        }
        if (tangents != NULL){
            memcpy(&(buffer[destIndex*sizeof(float)]), glm::value_ptr(tangents[i]), sizePrimitives);
            destIndex += 3;
        }
        if (colors != NULL){
            memcpy(&(buffer[destIndex*sizeof(float)]), glm::value_ptr(colors[i]), sizePrimitives);
            destIndex += 3;
        }
        if (textureCoords != NULL){
            memcpy(&(buffer[destIndex*sizeof(float)]), glm::value_ptr(textureCoords[i]), sizeTexCoords);
            destIndex += 2;
        }
        if (textureCoords2 != NULL){
            memcpy(&(buffer[destIndex*sizeof(float)]), glm::value_ptr(textureCoords2[i]), sizeTexCoords);
            destIndex += 2;
        }
        // vertices
        memcpy(&(buffer[destIndex*sizeof(float)]), glm::value_ptr(vertices[i]), sizePrimitives);
        destIndex += 3;
        
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount*indicesSize, indicesDest,GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // bind
    
    // clean up cpu memory
    switch (indexType){
        case GL_UNSIGNED_BYTE:
            delete []static_cast<GLubyte*>(indicesDest);
            break;
        case GL_UNSIGNED_SHORT:
            delete []static_cast<GLushort*>(indicesDest);
            break;
        case GL_UNSIGNED_INT:
            delete []static_cast<int*>(indicesDest);
            break;
    }
#endif
}

void MeshComponent::Release(){
#ifdef RENDER_E_NO_VBO    
	if (buffer != NULL){
        delete []buffer;
        delete [] ((unsigned char*)indices);
        buffer = NULL;
        indices = NULL;
    }
#else
    if (vboName != 0){
        glDeleteBuffers(1, &vboName);
        glDeleteBuffers(1, &vboElements);
        vboName = 0;
    }
#endif
}

}
