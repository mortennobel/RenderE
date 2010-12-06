/* 
 * File:   Mesh.h
 * Author: morten
 *
 * Created on November 12, 2010, 8:51 PM
 */

#ifndef MESH_H
#define	MESH_H

#include "math/Vector3.h"
#include "math/Vector2.h"
#include "Component.h"

namespace render_e {
class MeshComponent : public Component {
public:
    MeshComponent();
    virtual ~MeshComponent();
    void Render();
    void InitMesh(Vector3 *vertices, Vector3 *normals, Vector3 *tangent,
        Vector2 *textureCoords, Vector2 *textureCoords2, int verticeCount);
    void Release();
private:
    unsigned int vboName;
    int verticeCount;
};
}
#endif	/* MESH_H */

