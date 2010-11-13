/* 
 * File:   Mesh.cpp
 * Author: morten
 * 
 * Created on November 12, 2010, 8:51 PM
 */

#include "Mesh.h"

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
Mesh::Mesh()
:Component(MeshType), vboName(0){
}

Mesh::~Mesh() {
    if (vboName!= 0){
        Release();
    }
}

void Mesh::Render(){
    /*
    unsigned int vertexBufferSize = sizeof(float)*3*verticeCount;
	// bind buffer (set active)
	glBindBuffer(GL_ARRAY_BUFFER, vboName);
	// vertex pointer to buffer
	glVertexPointer(3, GL_FLOAT, 0,BUFFER_OFFSET(0));
	// normal pointer to buffer
	glNormalPointer(GL_FLOAT, 0, BUFFER_OFFSET(vertexBufferSize));
	// texcoord pointer to buffer
	glTexCoordPointer(2, GL_FLOAT, 0, BUFFER_OFFSET(vertexBufferSize*2));
    
    glEnable(GL_PRIMITIVE_RESTART_NV);
    glPrimitiveRestartIndexNV(0xFFFFFFFFU);
    glDisable(GL_PRIMITIVE_RESTART_NV);
    */
    glColor3f(1,0,0);
    glutSolidTeapot(1);
    std::cout<<"Draw teapot"<<std::endl;
}

void Mesh::InitMesh(Vector3 *vertices, Vector2 *textureCoords, Vector3 *normals, /*Vector3 *tangent,*/ 
        int verticeCount){
    /*
    if (vboName!=0){
        Release();
    }
    this->verticeCount = verticeCount;
    unsigned int buffersize = sizeof(float)*(3+3+2)*verticeCount;
    // create temp buffer
	float *buffer = new float[buffersize];
    // copy data to tmp buffer
	// data is organized [vertices, normals, texCoords]
	memcpy(buffer,vertices,sizeof(float)*3*verticeCount);
	memcpy(buffer+3*verticeCount,normals,sizeof(float)*3*verticeCount);
	memcpy(buffer+2*3*verticeCount,textureCoords,sizeof(float)*2*verticeCount);
    
    glGenBuffers(1,&vboName);
    // Bind buffer (set buffer active)
	glBindBuffer(GL_ARRAY_BUFFER, vboName); // bind
	// copy data to buffer
	glBufferData(GL_ARRAY_BUFFER, buffersize, buffer,GL_STATIC_DRAW);
    */
}

void Mesh::Release(){
    glDeleteBuffers(1, &vboName);
    vboName = 0;
}

}
