/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#ifndef CAMERA_H
#define	CAMERA_H

#include <cassert>

#include "RenderBase.h"
#include "Component.h"
#include <glm/glm.hpp>

namespace render_e {

enum CameraMode { ORTHOGRAPHIC, PERSPECTIVE };
enum CameraBuffer {
    COLOR_BUFFER = 1, 
    DEPTH_BUFFER = 2,
    STENCIL_BUFFER = 4
};

//  forward declaration
class Texture2D;

class Camera : public Component {
public:
    Camera();
    virtual ~Camera();
    void SetOrthogonal();
    void SetProjection(float fieldOfView, float aspect, float nearPlane, float farPlane);
    void SetOrthographic(float left, float right, float bottom,	float top,float nearPlane, float farPlane);
    CameraMode GetCameraMode(){ return cameraMode; }
    float GetFieldOfView(){ assert(cameraMode==PERSPECTIVE); return fieldOfView; }
    float GetAspect(){ assert(cameraMode==PERSPECTIVE); return aspect; }
    float GetNearPlane(){ return nearPlane; }
    float GetFarPlane(){ return farPlane; }    
    float GetLeft(){ assert (cameraMode==ORTHOGRAPHIC); return left; }
    float GetRight(){ assert (cameraMode==ORTHOGRAPHIC); return right; }
    float GetBottom(){ assert (cameraMode==ORTHOGRAPHIC); return bottom; }
    float GetTop(){ assert (cameraMode==ORTHOGRAPHIC); return top; }
    void SetClearMask(int clearBitMask);
    int GetClearMask();
    
    void Setup(int viewportWidth, int viewportHeight);
    void TearDown();
    void SetClearColor(glm::vec4 clearColor);
    glm::vec4 GetClearColor(){ return clearColor; }
    bool IsRenderToTexture(){ return renderToTexture; }
    void SetRenderToTexture( bool doRenderToTexture , CameraBuffer framebufferTargetType, TextureBase *texture);
    void BindFrameBufferObject();
    void UnBindFrameBufferObject();
	float *GetShadowMatrix(glm::mat4 &modelTransform);
private:
    CameraMode cameraMode;
    float fieldOfView;
    float aspect;
    float nearPlane;
    float farPlane;
    float left;
 	float right;
 	float bottom;
 	float top;
    int clearMask;
    int clearMaskNative;
    glm::vec4 clearColor;
    bool renderToTexture;
    unsigned int framebufferId;
    unsigned int renderBufferId;
    int framebufferTargetType;
    unsigned int framebufferTextureId;
    unsigned int framebufferTextureType;
    int fboWidth;
    int fboHeight;
	glm::mat4 shadowMatrix;
	glm::mat4 shadowMatrixMultiplied;
};
}
#endif	/* CAMERA_H */

