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
class Mesh : public Component {
public:
    Mesh();
    virtual ~Mesh();
    void Render();
    void InitMesh(Vector3 *vertices, Vector2 *textureCoords, Vector3 *normals, /*Vector3 *tangent,*/ 
        int verticeCount);
    void Release();
private:
    unsigned int vboName;
    int verticeCount;
};
}
#endif	/* MESH_H */

