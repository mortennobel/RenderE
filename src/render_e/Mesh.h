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
    Vector3 *GetColors();
    Vector2 *GetTextureCoords1();
    Vector2 *GetTextureCoords2();
    int GetPrimitiveCount();
    int *GetIndices();
    int GetIndicesCount();
    
    void SetVertices(std::vector<Vector3> vertices){ this->vertices = vertices;}
    void SetNormals(std::vector<Vector3> normals){ this->normals = normals;}
    void SetTangents(std::vector<Vector3> tangents){ this->tangents = tangents;}
    void SetColors(std::vector<Vector3> colors){ this->colors = colors; }
    void SetTextureCoords1(std::vector<Vector2> textureCoords1){ this->textureCoords1 = textureCoords1;}
    void SetTextureCoords2(std::vector<Vector2> textureCoords2){ this->textureCoords2 = textureCoords2;}
    void SetIndices(std::vector<int> indices){this->indices = indices;}
    
    // setters using pointers
    void SetVertices(Vector3 *vertices, int length);
    void SetNormals(Vector3 *normals, int length);
    void SetTangents(Vector3 *tangents, int length);
    void SetColors(Vector3 *tangents, int length);
    void SetTextureCoords1(Vector2 *textureCoords1, int length);
    void SetTextureCoords2(Vector2 *textureCoords2, int length);
    void SetIndices(int *indices, int length);
    
    /**
     * Validates mesh:
     * Check size of primitives
     * Check bounds of indices
     * @return true if valid
     */
    bool IsValid();
private:
    std::vector<Vector3> vertices;
    std::vector<Vector3> normals;
    std::vector<Vector3> tangents;
    std::vector<Vector3> colors;
    std::vector<Vector2> textureCoords1;
    std::vector<Vector2> textureCoords2;
    std::vector<int>     indices;
    
};
}

#endif	/* MESH_H */

