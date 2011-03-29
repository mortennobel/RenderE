/* 
 * File:   Mesh.h
 * Author: morten
 *
 * Created on December 6, 2010, 11:05 AM
 */

#ifndef MESH_H
#define	MESH_H

#include <vector>
#include <glm/glm.hpp>


namespace render_e {
class Mesh {
public:
    Mesh();
    Mesh(const Mesh& orig);
    virtual ~Mesh();
    
    void ComputeNormals();

    glm::vec3 *GetVertices();
    glm::vec3 *GetNormals();
    glm::vec3 *GetTangents();
    glm::vec3 *GetColors();
    glm::vec2 *GetTextureCoords1();
    glm::vec2 *GetTextureCoords2();
    int GetPrimitiveCount();
    int *GetIndices();
    int GetIndicesCount();
    
    void SetVertices(std::vector<glm::vec3> vertices){ this->vertices = vertices;}
    void SetNormals(std::vector<glm::vec3> normals){ this->normals = normals;}
    void SetTangents(std::vector<glm::vec3> tangents){ this->tangents = tangents;}
    void SetColors(std::vector<glm::vec3> colors){ this->colors = colors; }
    void SetTextureCoords1(std::vector<glm::vec2> textureCoords1){ this->textureCoords1 = textureCoords1;}
    void SetTextureCoords2(std::vector<glm::vec2> textureCoords2){ this->textureCoords2 = textureCoords2;}
    void SetIndices(std::vector<int> indices){this->indices = indices;}
    
    // setters using pointers
    void SetVertices(glm::vec3 *vertices, int length);
    void SetNormals(glm::vec3 *normals, int length);
    void SetTangents(glm::vec3 *tangents, int length);
    void SetColors(glm::vec3 *tangents, int length);
    void SetTextureCoords1(glm::vec2 *textureCoords1, int length);
    void SetTextureCoords2(glm::vec2 *textureCoords2, int length);
    void SetIndices(int *indices, int length);
    
    /**
     * Validates mesh:
     * Check size of primitives
     * Check bounds of indices
     * @return true if valid
     */
    bool IsValid();
private:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> tangents;
    std::vector<glm::vec3> colors;
    std::vector<glm::vec2> textureCoords1;
    std::vector<glm::vec2> textureCoords2;
    std::vector<int>     indices;
    
};
}

#endif	/* MESH_H */

