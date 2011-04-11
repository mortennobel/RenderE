/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#ifndef PARTICLESYSTEM_H
#define	PARTICLESYSTEM_H

#include "Component.h"

namespace render_e {

class ParticleSystem : public Component {
public:
    ParticleSystem();
    virtual ~ParticleSystem();
    virtual void Update() {}
private:
    ParticleSystem(const ParticleSystem& orig); // unsupported
    bool oneShoot;
    
};

}
#endif	/* PARTICLESYSTEM_H */

