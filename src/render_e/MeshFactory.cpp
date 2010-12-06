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
Mesh *MeshFactory::Tetrahedron(){
    Vector3 p0(0.,0.,0.);
	Vector3 p1(1.,0.,0.);
	Vector3 p2(0.5f,0.,Mathf::Sqrt(0.75f));
	Vector3 p3(0.5f,Mathf::Sqrt(0.75f),Mathf::Sqrt(0.75f)/3.0f);

    vector<Vector3> vertices;
    vertices.push_back(p0);
    vertices.push_back(p1);
    vertices.push_back(p2);
    
    vertices.push_back(p0);
    vertices.push_back(p2);
    vertices.push_back(p3);
    
    vertices.push_back(p2);
    vertices.push_back(p1);
    vertices.push_back(p3);
    
    vertices.push_back(p0);
    vertices.push_back(p3);
    vertices.push_back(p1);
    
    vector<int> triangles;
    for (int i=0;i<12;i++){
        triangles.push_back(i);
    }
    
    Vector2 uv0(0,0);
    Vector2 uv1(1,0);
    Vector2 uv2(0.5f,1);
    
    vector<Vector2> uv;
    uv.push_back(uv0);
    uv.push_back(uv1);
    uv.push_back(uv2);

    uv.push_back(uv0);
    uv.push_back(uv1);
    uv.push_back(uv2);

    uv.push_back(uv0);
    uv.push_back(uv1);
    uv.push_back(uv2);

    uv.push_back(uv0);
    uv.push_back(uv1);
    uv.push_back(uv2);

    Mesh *m = new Mesh();
    m->SetVertices(vertices);
    m->SetTextureCoords1(uv);
    m->SetTriangles(triangles);
    m->ComputeNormals();
    return m;
}
}

