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
        Vector3 *vv = (Vector3*)(&(buffer[index*stride]));
        Vector3 v = vv[0];
        cout<<index<<"  "<<v[0]<<","<<v[1]<<","<<v[2]<<endl;
        if (normalOffset!=-1){
            Vector3 n = vv[1];
            cout<<index<<"      "<<n[0]<<","<<n[1]<<","<<n[2]<<endl;
        }
    }
    cout<<"Print rendering start"<<endl;
}
#endif RENDER_E_NO_VBO

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
        
        Vector3 *vv = (Vector3*)(&(buffer[index*(stride)]));
        
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
        // bind buffer (set active)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboElements);
        glDrawElements(GL_TRIANGLES, indicesCount, indexType, BUFFER_OFFSET(0) );
        
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
    int *indices = mesh->GetIndices(); // todo rename
    indicesCount = mesh->GetIndicesCount();
    Release();
    
    // Calculate size of data
    
    int sizePrimitives = sizeof(Vector3);
    int offset = sizePrimitives; // vertices
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
    int sizeTexCoords = sizeof(Vector2);
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
    stride = offset;
    
    // create temp buffer
    unsigned int buffersize = offset*primitiveCount;
    
    void *indicesDest;
    int indicesSize;
    if (primitiveCount < 0xff){
        indicesSize = sizeof(char);
        indexType = GL_UNSIGNED_BYTE;
        GLubyte *byteBuffer = new GLubyte[indicesCount];
        for (int i=0;i<indicesCount;i++){
            byteBuffer[i] = indices[i];
        }
        indicesDest = byteBuffer;
    } else if (primitiveCount < 0xffff){
        indicesSize = sizeof(short);
        indexType = GL_UNSIGNED_SHORT;
        GLushort *shortBuffer = new GLushort[indicesCount];
        for (int i=0;i<indicesCount;i++){
            shortBuffer[i] = indices[i];
        }
        indicesDest = shortBuffer;
    } else {
        indicesSize = sizeof(int);
        indexType = GL_UNSIGNED_INT;
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
    float *bufferAsFloat = (float *)buffer;
    
    // Memory layout: Vertex0, Normal0, ..., Vertex1, Normal1, ...
    // This layout gives a better performance, since the data that belongs
    // together are located close to each other
    
    int destIndex = 0;
    for (int i=0;i<primitiveCount;i++){
        memcpy(&bufferAsFloat[destIndex], vertices[i].Get(), sizePrimitives);
        
        destIndex += 3;
        if (normals != NULL){
            memcpy(&bufferAsFloat[destIndex], normals[i].Get(), sizePrimitives);
            destIndex += 3;
        }
        if (tangents != NULL){
            memcpy(&bufferAsFloat[destIndex], tangents[i].Get(), sizePrimitives);
            destIndex += 3;
        }
        if (colors != NULL){
            memcpy(&bufferAsFloat[destIndex], colors[i].Get(), sizePrimitives);
            destIndex += 3;
        }
        if (textureCoords != NULL){
            memcpy(&bufferAsFloat[destIndex], textureCoords[i].Get(), sizeTexCoords);
            destIndex += 2;
        }
        if (textureCoords2 != NULL){
            memcpy(&bufferAsFloat[destIndex], textureCoords2[i].Get(), sizeTexCoords);
            destIndex += 2;
        }
        
    }
        
    // print buffer
    /*
    using namespace std;
    cout<<"Memory dump start"<<endl;
    for (int i=0;i<primitiveCount*(offset/sizeof(float));i++){
        if (i%(offset/sizeof(float))==0){
            cout << endl;
        }
        cout<<bufferAsFloat[i]<<", ";
    }
    cout<<endl<<"Memory dump end"<<endl;
    */
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount*indicesSize, indices,GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // bind
    
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
