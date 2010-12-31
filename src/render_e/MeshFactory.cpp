/* 
 * File:   MeshFactory.cpp
 * Author: morten
 * 
 * Created on December 6, 2010, 12:16 PM
 */

#include "MeshFactory.h"

#include <vector>
#include "math/Vector3.h"
#include "math/Vector2.h"
#include "math/Mathf.h"

using std::vector;


namespace render_e {
Mesh *MeshFactory::CreateTetrahedron(){
    Vector3 p0(0.,0.,0.);
	Vector3 p1(1.,0.,0.);
	Vector3 p2(0.5f,0.,Mathf::Sqrt(0.75f));
	Vector3 p3(0.5f,Mathf::Sqrt(0.75f),Mathf::Sqrt(0.75f)/3.0f);

    Vector3 vertices [] = {
        p0,p1,p2,
        p0,p2,p3,
        p2,p1,p3,
        p0,p3,p1
    };
    
    vector<int> indices;
    for (int i=0;i<12;i++){
        indices.push_back(i);
    }
    
    Vector2 uv0(0,0);
    Vector2 uv1(1,0);
    Vector2 uv2(0.5f,1);
    
    Vector2 uv[] = {
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

    // vertex coords array
    Vector3 vertices[] = {Vector3(1,1,1),  Vector3(-1,1,1),  Vector3(-1,-1,1),  Vector3(1,-1,1),        // v0-v1-v2-v3
                          Vector3(1,1,1),  Vector3(1,-1,1),  Vector3(1,-1,-1),  Vector3(1,1,-1),        // v0-v3-v4-v5
                          Vector3(1,1,1),  Vector3(1,1,-1),  Vector3(-1,1,-1),  Vector3(-1,1,1),        // v0-v5-v6-v1
                          Vector3(-1,1,1), Vector3(-1,1,-1),  Vector3(-1,-1,-1),  Vector3(-1,-1,1),    // v1-v6-v7-v2
                          Vector3(-1,-1,-1),  Vector3(1,-1,-1),  Vector3(1,-1,1),  Vector3(-1,-1,1),    // v7-v4-v3-v2
                          Vector3(1,-1,-1),  Vector3(-1,-1,-1),  Vector3(-1,1,-1),  Vector3(1,1,-1)};   // v4-v7-v6-v5

    // normal array
    Vector3 normals[] = {Vector3(0,0,1),  Vector3(0,0,1),  Vector3(0,0,1),  Vector3(0,0,1),             // v0-v1-v2-v3
                         Vector3(1,0,0),  Vector3(1,0,0),  Vector3(1,0,0), Vector3(1,0,0),              // v0-v3-v4-v5
                         Vector3(0,1,0),  Vector3(0,1,0),  Vector3(0,1,0), Vector3(0,1,0),              // v0-v5-v6-v1
                         Vector3(-1,0,0),  Vector3(-1,0,0), Vector3(-1,0,0),  Vector3(-1,0,0),          // v1-v6-v7-v2
                         Vector3(0,-1,0),  Vector3(0,-1,0),  Vector3(0,-1,0),  Vector3(0,-1,0),         // v7-v4-v3-v2
                         Vector3(0,0,-1),  Vector3(0,0,-1),  Vector3(0,0,-1),  Vector3(0,0,-1)};        // v4-v7-v6-v5

    // color array
    Vector3 colors[] = {Vector3(1,1,1),  Vector3(1,1,0),  Vector3(1,0,0),  Vector3(1,0,1),              // v0-v1-v2-v3
                        Vector3(1,1,1),  Vector3(1,0,1),  Vector3(0,0,1),  Vector3(0,1,1),              // v0-v3-v4-v5
                        Vector3(1,1,1),  Vector3(0,1,1),  Vector3(0,1,0),  Vector3(1,1,0),              // v0-v5-v6-v1
                        Vector3(1,1,0),  Vector3(0,1,0),  Vector3(0,0,0),  Vector3(1,0,0),              // v1-v6-v7-v2
                        Vector3(0,0,0),  Vector3(0,0,1),  Vector3(1,0,1),  Vector3(1,0,0),              // v7-v4-v3-v2
                        Vector3(0,0,1),  Vector3(0,0,0),  Vector3(0,1,0),  Vector3(0,1,1)};             // v4-v7-v6-v5

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
    m->SetIndices(indices,3*2*6);
    return m;
}

// based on the code in the OpenGL red book (chapter 2, the example at the end)

void drawtri(Vector3 a, Vector3 b, Vector3 c, int div, float r, vector<Vector3> &vertices, vector<Vector3> &normals) {
    if (div<=0) {
        normals.push_back(a);
        normals.push_back(b);
        normals.push_back(c);
        vertices.push_back(a*r);
        vertices.push_back(b*r);
        vertices.push_back(c*r);
    } else {
        Vector3 ab, ac, bc;
        for (int i=0;i<3;i++) {
            ab[i]=(a[i]+b[i])/2;
            ac[i]=(a[i]+c[i])/2;
            bc[i]=(b[i]+c[i])/2;
        }
        ab.Normalize();
        ac.Normalize();
        bc.Normalize();
        drawtri(a, ab, ac, div-1, r,vertices, normals);
        drawtri(b, bc, ab, div-1, r,vertices, normals);
        drawtri(c, ac, bc, div-1, r,vertices, normals);
        drawtri(ab, bc, ac, div-1, r,vertices, normals);   
    }  
}

Mesh *MeshFactory::CreateICOSphere(int subdivisions, float radius){
    #define X .525731112119133606f
    #define Z .850650808352039932f

    Vector3 vdata[12] = {    
        Vector3(-X, 0.0, Z), Vector3(X, 0.0, Z), Vector3(-X, 0.0, -Z), Vector3(X, 0.0, -Z),    
        Vector3(0.0, Z, X), Vector3(0.0, Z, -X), Vector3(0.0, -Z, X), Vector3(0.0, -Z, -X),    
        Vector3(Z, X, 0.0), Vector3(-Z, X, 0.0), Vector3(Z, -X, 0.0), Vector3(-Z, -X, 0.0) 
    };
    int tindices[20][3] = { 
        {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},    
        {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},    
        {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6}, 
        {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };

    vector<Vector3> vertices;
    vector<Vector3> normals;
    
    for (int i=0;i<20;i++)
        drawtri(vdata[tindices[i][0]], vdata[tindices[i][1]], vdata[tindices[i][2]], subdivisions, radius, vertices, normals);

    vector<int> indices;
    for (int i=0;i<vertices.size();i++){
        indices.push_back(i);
    }
    Mesh *m = new Mesh();
    m->SetVertices(vertices);
    m->SetNormals(normals);
    m->SetIndices(indices);
    return m;
}
}

