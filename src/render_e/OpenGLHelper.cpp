/* 
 * File:   OpenGLHelper.cpp
 * Author: morten
 * 
 * Created on March 6, 2011, 3:05 PM
 */

#include "OpenGLHelper.h"

#include <iostream>

OpenGLHelper::OpenGLHelper() {
}

OpenGLHelper::OpenGLHelper(const OpenGLHelper& orig) {
}

OpenGLHelper::~OpenGLHelper() {
}

std::string OpenGLHelper::GetFrameBufferStatusString(GLenum code){
    using namespace std;
    switch (code){
        case GL_FRAMEBUFFER_COMPLETE:
            return "Framebuffer ok";
        case GL_FRAMEBUFFER_UNDEFINED:
            return "Framebuffer undefined";
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            return "Framebuffer incomplete attachment";
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            return "Framebuffer incomplete missing attachment";
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            return "Framebuffer incomplete read buffer";
        case GL_FRAMEBUFFER_UNSUPPORTED:
            return "Framebuffer unsupported";
        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
            return "Framebuffer incomplete multisample";
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
            return "FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
        case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
            return "FRAMEBUFFER_INCOMPLETE_FORMATS";
        default:
            return "Unknown framebuffer status ";
    }
}

void OpenGLHelper::PrintErrors(){
    using namespace std;
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR) {
        const GLubyte* errorStr = gluErrorString(errorCode);
		if (errorStr==NULL){
			const char *ERR = "Unknown";
			errorStr=(GLubyte*)ERR;
		}
        std::cout << " " << errorCode << " " << errorStr <<
            std::endl;
    }
}