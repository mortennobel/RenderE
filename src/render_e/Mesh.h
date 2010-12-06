/* 
 * File:   Mesh.h
 * Author: morten
 *
 * Created on December 6, 2010, 11:05 AM
 */

#ifndef MESH_H
#define	MESH_H

#include <vector>
#include "math/Vector3.h"
#include "math/Vector2.h"


namespace render_e {
class Mesh {
public:
    Mesh();
    Mesh(const Mesh& orig);
    virtual ~Mesh();
    
    void ComputeNormals();

    Vector3 *GetVertices();
    Vector3 *GetNormals();
    Vector3 *GetTangents();
    Vector2 *GetTextureCoords1();
    Vector2 *GetTextureCoords2();
    int GetPrimitiveCount();
    int *GetTriangles();
    int GetTriangleCount();
    
    void SetVertices(std::vector<Vector3> vertices){ this->vertices = vertices;}
    void SetNormals(std::vector<Vector3> normals){ this->normals = normals;}
    void SetTangents(std::vector<Vector3> tangents){ this->tangents = tangents;}
    void SetTextureCoords1(std::vector<Vector2> textureCoords1){ this->textureCoords1 = textureCoords1;}
    void SetTextureCoords2(std::vector<Vector2> textureCoords2){ this->textureCoords2 = textureCoords2;}
    void SetTriangles(std::vector<int> triangles){this->triangles = triangles;}
private:
    std::vector<Vector3> vertices;
    std::vector<Vector3> normals;
    std::vector<Vector3> tangents;
    std::vector<Vector2> textureCoords1;
    std::vector<Vector2> textureCoords2;
    std::vector<int>     triangles;
    
};
}

#endif	/* MESH_H */

