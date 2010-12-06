/* 
 * File:   Mesh.h
 * Author: morten
 *
 * Created on November 12, 2010, 8:51 PM
 */

#ifndef MESH_COMPONENT_H
#define	MESH_COMPONENT_H

#include "math/Vector3.h"
#include "math/Vector2.h"
#include "Component.h"
#include "Mesh.h"

namespace render_e {
class MeshComponent : public Component {
public:
    MeshComponent();
    virtual ~MeshComponent();
    void Render();
    void SetMesh(Mesh *mesh);
    void Release();
private:
    Mesh *mesh;
    unsigned int vboName;
    int verticeCount;
    int *triangles;
    int triangleCount;

    int normalOffset;
    int tangentOffset;
    int texture1Offset;
    int texture2Offset;
};
}
#endif	/* MESH_COMPONENT_H */

