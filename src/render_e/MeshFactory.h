/* 
 * File:   MeshFactory.h
 * Author: morten
 *
 * Created on December 6, 2010, 12:16 PM
 */

#ifndef MESHFACTORY_H
#define	MESHFACTORY_H

#include "Mesh.h"

namespace render_e {
class MeshFactory {
public:
    // static Mesh *CreateCube(float size);
    static Mesh *CreateTetrahedron();
    static Mesh *CreateICOSphere(int subdivisions=2, float radius=1.0f);
    static Mesh *CreateCube();
private:
    MeshFactory();

};
}
#endif	/* MESHFACTORY_H */

