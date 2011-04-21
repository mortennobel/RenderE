/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#include "MeshFactory.h"

#include <vector>
#include <iostream>
#include "Mathf.h"
#include <glm/gtx/fast_square_root.hpp>

using std::vector;


namespace render_e {
Mesh *MeshFactory::CreateTetrahedron(){
    glm::vec3 p0(0.,0.,0.);
	glm::vec3 p1(1.,0.,0.);
	glm::vec3 p2(0.5f,0.,glm::gtx::fast_square_root::fastSqrt(0.75f));
	glm::vec3 p3(0.5f,glm::gtx::fast_square_root::fastSqrt	(0.75f),glm::gtx::fast_square_root::fastSqrt(0.75f)/3.0f);

    glm::vec3 vertices [] = {
        p0,p1,p2,
        p0,p2,p3,
        p2,p1,p3,
        p0,p3,p1
    };
    
    vector<int> indices;
    for (int i=0;i<12;i++){
        indices.push_back(i);
    }
    
    glm::vec2 uv0(0,0);
    glm::vec2 uv1(1,0);
    glm::vec2 uv2(0.5f,1);
    
    glm::vec2 uv[] = {
        uv0,uv1,uv2,
        uv0,uv1,uv2,
        uv0,uv1,uv2,
        uv0,uv1,uv2
    };
    

    Mesh *m = new Mesh();
    m->SetVertices(vertices,12);
    m->SetTextureCoords1(uv,12);
    m->SetIndices(indices);
    m->ComputeNormals();
    return m;
}

Mesh *MeshFactory::CreateCube(){
    // Source from http://www.songho.ca/opengl/gl_vertexarray.html
    // cube ///////////////////////////////////////////////////////////////////////
    //    v6----- v5
    //   /|      /|
    //  v1------v0|
    //  | |     | |
    //  | |v7---|-|v4
    //  |/      |/
    //  v2------v3

    using namespace glm;
    // vertex coords array
    vec3 vertices[] = {vec3(1,1,1), vec3(-1,1,1), vec3(-1,-1,1), vec3(1,-1,1),        // v0-v1-v2-v3
                          vec3(1,1,1), vec3(1,-1,1), vec3(1,-1,-1), vec3(1,1,-1),        // v0-v3-v4-v5
                          vec3(1,1,1), vec3(1,1,-1), vec3(-1,1,-1), vec3(-1,1,1),        // v0-v5-v6-v1
                          vec3(-1,1,1), vec3(-1,1,-1), vec3(-1,-1,-1), vec3(-1,-1,1),    // v1-v6-v7-v2
                          vec3(-1,-1,-1), vec3(1,-1,-1), vec3(1,-1,1), vec3(-1,-1,1),    // v7-v4-v3-v2
                          vec3(1,-1,-1), vec3(-1,-1,-1), vec3(-1,1,-1), vec3(1,1,-1)};   // v4-v7-v6-v5

    // normal array
    vec3 normals[] = {vec3(0,0,1),  vec3(0,0,1),  vec3(0,0,1),  vec3(0,0,1),             // v0-v1-v2-v3
                         vec3(1,0,0),  vec3(1,0,0),  vec3(1,0,0), vec3(1,0,0),              // v0-v3-v4-v5
                         vec3(0,1,0),  vec3(0,1,0),  vec3(0,1,0), vec3(0,1,0),              // v0-v5-v6-v1
                         vec3(-1,0,0),  vec3(-1,0,0), vec3(-1,0,0),  vec3(-1,0,0),          // v1-v6-v7-v2
                         vec3(0,-1,0),  vec3(0,-1,0),  vec3(0,-1,0),  vec3(0,-1,0),         // v7-v4-v3-v2
                         vec3(0,0,-1),  vec3(0,0,-1),  vec3(0,0,-1),  vec3(0,0,-1)};        // v4-v7-v6-v5

    // color array
    vec3 colors[] = {vec3(1,1,1),  vec3(1,1,0),  vec3(1,0,0),  vec3(1,0,1),              // v0-v1-v2-v3
                        vec3(1,1,1),  vec3(1,0,1),  vec3(0,0,1),  vec3(0,1,1),              // v0-v3-v4-v5
                        vec3(1,1,1),  vec3(0,1,1),  vec3(0,1,0),  vec3(1,1,0),              // v0-v5-v6-v1
                        vec3(1,1,0),  vec3(0,1,0),  vec3(0,0,0),  vec3(1,0,0),              // v1-v6-v7-v2
                        vec3(0,0,0),  vec3(0,0,1),  vec3(1,0,1),  vec3(1,0,0),              // v7-v4-v3-v2
                        vec3(0,0,1),  vec3(0,0,0),  vec3(0,1,0),  vec3(0,1,1)};             // v4-v7-v6-v5

    vec2 uvs[] = {vec2(1,1),  vec2(1,1),  vec2(1,0),  vec2(1,0),                    // v0-v1-v2-v3
                        vec2(1,1),  vec2(1,0),  vec2(0,0),  vec2(0,1),              // v0-v3-v4-v5
                        vec2(1,1),  vec2(0,1),  vec2(0,1),  vec2(1,1),              // v0-v5-v6-v1
                        vec2(1,1),  vec2(0,1),  vec2(0,0),  vec2(1,0),              // v1-v6-v7-v2
                        vec2(0,0),  vec2(0,0),  vec2(1,0),  vec2(1,0),              // v7-v4-v3-v2
                        vec2(0,0),  vec2(0,0),  vec2(0,1),  vec2(0,1)};             // v4-v7-v6-v5
    
    // index array of vertex array for glDrawElements()
    // Notice the indices are listed straight from beginning to end as exactly
    // same order of vertex array without hopping, because of different normals at
    // a shared vertex. For this case, glDrawArrays() and glDrawElements() have no
    // difference.
    int indices[] = {
        0,1,2,
        0,2,3,
        4,5,6,
        4,6,7,
        8,9,10,
        8,10,11,
        12,13,14,
        12,14,15,
        16,17,18,
        16,18,19,
        20,21,22,
        20,22,23
        };

    Mesh *m = new Mesh();
    m->SetVertices(vertices,4*6);
    m->SetNormals(normals,4*6);
    m->SetColors(colors,4*6);
    m->SetTextureCoords1(uvs, 4*6);
    m->SetIndices(indices,3*2*6);
    return m;
}

// based on the code in the OpenGL red book (chapter 2, the example at the end)

void drawtri(glm::vec3 a, glm::vec3 b, glm::vec3 c, int div, float r, 
        vector<glm::vec3> &vertices, vector<glm::vec3> &normals, 
        vector<glm::vec2> &uvs) {
    if (div<=0) {
        normals.push_back(a);		
        normals.push_back(c);
        normals.push_back(b);
        vertices.push_back(a*r);
        vertices.push_back(c*r);
        vertices.push_back(b*r);
        uvs.push_back(glm::vec2(0,0)); // todo - use sphere mapping
        uvs.push_back(glm::vec2(0,0));
        uvs.push_back(glm::vec2(0,0));
    } else {
        glm::vec3 ab, ac, bc;
        for (int i=0;i<3;i++) {
            ab[i]=(a[i]+b[i])/2;
            ac[i]=(a[i]+c[i])/2;
            bc[i]=(b[i]+c[i])/2;
        }
        ab = glm::normalize(ab);
        ac = glm::normalize(ac);
        bc = glm::normalize(bc);
        drawtri(a, ab, ac, div-1, r,vertices, normals, uvs);
        drawtri(b, bc, ab, div-1, r,vertices, normals, uvs);
        drawtri(c, ac, bc, div-1, r,vertices, normals, uvs);
        drawtri(ab, bc, ac, div-1, r,vertices, normals, uvs);   
    }  
}

Mesh *MeshFactory::CreateICOSphere(int subdivisions, float radius){
    #define X .525731112119133606f
    #define Z .850650808352039932f

    glm::vec3 vdata[12] = {    
        glm::vec3(-X, 0.0, Z), glm::vec3(X, 0.0, Z), glm::vec3(-X, 0.0, -Z), glm::vec3(X, 0.0, -Z),    
        glm::vec3(0.0, Z, X), glm::vec3(0.0, Z, -X), glm::vec3(0.0, -Z, X), glm::vec3(0.0, -Z, -X),    
        glm::vec3(Z, X, 0.0), glm::vec3(-Z, X, 0.0), glm::vec3(Z, -X, 0.0), glm::vec3(-Z, -X, 0.0) 
    };
    int tindices[20][3] = { 
        {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},    
        {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},    
        {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6}, 
        {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };

    vector<glm::vec3> vertices;
    vector<glm::vec3> normals;
    vector<glm::vec2> uvs;
    
    for (int i=0;i<20;i++)
        drawtri(vdata[tindices[i][0]], vdata[tindices[i][1]], vdata[tindices[i][2]], subdivisions, radius, vertices, normals, uvs);

    vector<int> indices;
    for (int i=0;i<vertices.size();i++){
        indices.push_back(i);
    }
    Mesh *m = new Mesh();
    m->SetVertices(vertices);
    m->SetNormals(normals);
    m->SetTextureCoords1(uvs);
    m->SetIndices(indices);
    return m;
}

Mesh *MeshFactory::CreatePlane(){
    vector<glm::vec3> vertices;
    vector<int> indices;
    vector<glm::vec2> uvs;
    
    for (int x=0;x<10;x++){
        for (int y=0;y<10;y++){
            glm::vec3 offset = glm::vec3(0.1*x,0.1*y,0);
            vertices.push_back(glm::vec3(0.,0.,0.)+offset);
            vertices.push_back(glm::vec3(.1,0.,0.)+offset);
            vertices.push_back(glm::vec3(.1,.1,0.)+offset);
            vertices.push_back(glm::vec3(0.,.1,0.)+offset);
            
            int indexOffset = (x*10+y)*4;
            indices.push_back(0+indexOffset);
            indices.push_back(1+indexOffset);
            indices.push_back(2+indexOffset);
            indices.push_back(0+indexOffset);
            indices.push_back(2+indexOffset);
            indices.push_back(3+indexOffset);
            
            glm::vec2 offsetUV = glm::vec2(0.1*x,0.1*y);
            uvs.push_back(glm::vec2(0.,0.)+offsetUV);
            uvs.push_back(glm::vec2(.1,0.)+offsetUV);
            uvs.push_back(glm::vec2(.1,.1)+offsetUV);
            uvs.push_back(glm::vec2(0.,.1)+offsetUV);
            
        }
    }

    Mesh *m = new Mesh();
    m->SetVertices(vertices);
    m->SetTextureCoords1(uvs);
    m->SetIndices(indices);
    m->ComputeNormals();
    return m;
}
}

