/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#ifndef RENDER_E_TIME_H
#define	RENDER_E_TIME_H

namespace render_e {

/// Contains time, deltaTime (time since last frame) and a frames counter
class FrameTime {
public:
    /// Return time since program start
    static float GetTime();
    
    /// Return delta time (time since last frame update)
    static float GetDeltaTime();
    
    /// Return the frameid
    static unsigned long GetFrame();
    
    /// update by RenderBase
    static void updateTime(float deltaTime);
private:
    /*FrameTime(); // static only - no class constructor
    FrameTime(const FrameTime& orig);
    virtual ~FrameTime();*/
    
    static float time;
    static float deltaTime;
    static unsigned long frameCounter;
};
}
#endif	/* RENDER_E_TIME_H */

