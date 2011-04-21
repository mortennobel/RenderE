/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
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
    static Mesh *CreatePlane();
private:
    MeshFactory();

};
}
#endif	/* MESHFACTORY_H */

