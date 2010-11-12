/* 
 * File:   Mesh.h
 * Author: morten
 *
 * Created on November 12, 2010, 8:51 PM
 */

#ifndef MESH_H
#define	MESH_H

#include "math/Vector3.h"
#include "Component.h"

namespace render_e {
class Mesh : public Component {
public:
    Mesh();
    virtual ~Mesh();
    void Render();
private:
    Vector3 *vertices;
    Vector3 *normals;
    Vector3 *tangent;
    int *triangles;
};
}
#endif	/* MESH_H */

