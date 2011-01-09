/* 
 * File:   Camera.h
 * Author: morten
 *
 * Created on October 31, 2010, 2:12 PM
 */

#ifndef CAMERA_H
#define	CAMERA_H

#include <cassert>

#include "RenderBase.h"
#include "math/Vector4.h"
#include "math/Matrix44.h"
#include "Component.h"

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
    /// Clear buffers in 
    void Clear();
    void Setup(int viewportWidth, int viewportHeight);
    void TearDown();
    void SetClearColor(Vector4 clearColor);
    Vector4 GetClearColor(){ return clearColor; }
    bool IsRenderToTexture(){ return renderToTexture; }
    void SetRenderToTexture( bool doRenderToTexture , CameraBuffer framebufferTargetType, TextureBase *texture);
    void BindFrameBufferObject();
    void UnBindFrameBufferObject();
	float *GetShadowMatrix();
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
    Vector4 clearColor;
    bool renderToTexture;
    unsigned int framebufferId;
    unsigned int renderBufferId;
    int framebufferTargetType;
    unsigned int framebufferTextureId;
    unsigned int framebufferTextureType;
    int fboWidth;
    int fboHeight;
	Matrix44 shadowMatrix;
};
}
#endif	/* CAMERA_H */

