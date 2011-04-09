/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#ifndef OPENGLHELPER_H
#define	OPENGLHELPER_H

#include <string>
#include "GL/glew.h"

namespace render_e {
///
/// Helper class that contains OpenGL specific code
///
class OpenGLHelper {
public:
    static std::string GetFrameBufferStatusString(GLenum code);
    /// helper function that prints OpenGL errors (if any)
    static void PrintErrors();
private:
    OpenGLHelper();
    OpenGLHelper(const OpenGLHelper& orig);
    virtual ~OpenGLHelper();
};

}

#endif	/* OPENGLHELPER_H */

