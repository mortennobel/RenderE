/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#include "FrameTime.h"

namespace render_e {

float FrameTime::time = 0.0f;
float FrameTime::deltaTime = 0.0f;
unsigned long FrameTime::frameCounter = 0L;

float FrameTime::GetTime(){
    return time;
}
    
float FrameTime::GetDeltaTime(){
    return deltaTime;
}
    
unsigned long FrameTime::GetFrame(){
    return frameCounter;
}

void FrameTime::updateTime(float deltaTime){
    FrameTime::deltaTime = deltaTime;
    time += deltaTime;
    frameCounter++;
}
}
