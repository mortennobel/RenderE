/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */
#include "Log.h"

#include <iostream>

namespace render_e {
void Log::LogMessage(std::string file, int lineNo, std::string message, LogType logType){
    if (logType>Info){
        std::cout<<file<<":"<<lineNo<<" ";
    }
    std::cout<<message<<std::endl;
}
}