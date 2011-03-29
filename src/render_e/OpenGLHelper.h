/* 
 * File:   OpenGLHelper.h
 * Author: morten
 *
 * Created on March 6, 2011, 3:05 PM
 */

#ifndef OPENGLHELPER_H
#define	OPENGLHELPER_H

#include <string>
#include "GL/glew.h"

/*
 * Helper class that contains OpenGL specific code
 */
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

#endif	/* OPENGLHELPER_H */

