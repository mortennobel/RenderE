/*
 *  render_base.h
 *  RenderE
 */
#ifndef RENDER_E_RENDERBASE_H
#define RENDER_E_RENDERBASE_H

#include <vector>
#include "SceneObject.h"

namespace render_e {

// forward declaration
class SceneObject;

class RenderBase {
public:
    void Display();

    void AddSceneObject(SceneObject *sceneObject);
    void DeleteSceneObject(SceneObject *sceneObject);
    
    void Init(void(*swapBuffersFunc)());

    /**
     * Singleton pattern
     * @return the render base instance
     */
    static RenderBase* Instance() {
        if (!s_instance) {
            s_instance = new RenderBase();
        }
        return s_instance;
    }
private:
    RenderBase();
    void RenderScene(const Matrix44 &cameraMatrix);
    static RenderBase *s_instance;
    std::vector<SceneObject*> sceneObjects;
    std::vector<SceneObject*> cameras;
    
    void(*swapBuffersFunc)();
};

}
#endif
