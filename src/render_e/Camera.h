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
#include "Component.h"

namespace render_e {

enum CameraType {ORTHOGRAPHIC, PERSPECTIVE};
enum ClearTypes {
    COLOR_BUFFER = 1, 
    DEPTH_BUFFER = 2,
    STENCIL_BUFFER = 4
};

class Camera : public Component{
public:
    Camera();
    Camera(const Camera& orig);
    virtual ~Camera();
    void SetOrthogonal();
    void SetProjection(float fieldOfView, float aspect, float nearPlane, float farPlane);
    void SetOrthographic(float left, float right, float bottom,	float top,float nearPlane, float farPlane);
    CameraType GetCameraType(){ return cameraType; }
    float GetFieldOfView(){ assert(cameraType==PERSPECTIVE); return fieldOfView; }
    float GetAspect(){ assert(cameraType==PERSPECTIVE); return aspect; }
    float GetNearPlane(){ return nearPlane; }
    float GetFarPlane(){ return farPlane; }    
    float GetLeft(){ assert (cameraType==ORTHOGRAPHIC); return left; }
    float GetRight(){ assert (cameraType==ORTHOGRAPHIC); return right; }
    float GetBottom(){ assert (cameraType==ORTHOGRAPHIC); return bottom; }
    float GetTop(){ assert (cameraType==ORTHOGRAPHIC); return top; }
    void SetClearMask(int clearBitMask);
    int GetClearMask();
    /// Clear buffers in 
    void Clear();
    void Setup();
    void SetClearColor(Vector4 &clearColor){ this->clearColor = clearColor; }
    Vector4 GetClearColor(){ return clearColor; }
private:
    CameraType cameraType;
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
};
}
#endif	/* CAMERA_H */

