/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#ifndef MESH_COMPONENT_H
#define	MESH_COMPONENT_H

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
    unsigned int vboName;
    unsigned int vboElements;
    int indicesCount;
    int vertexOffset;
    int normalOffset;
    int tangentOffset;
    int colorOffset;
    int texture1Offset;
    int texture2Offset;
    int triangleOffset;
    int stride;
    unsigned short indexType;
};
}
#endif	/* MESH_COMPONENT_H */

