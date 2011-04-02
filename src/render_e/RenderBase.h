/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#ifndef RENDER_E_RENDERBASE_H
#define RENDER_E_RENDERBASE_H

#include <vector>
#include <map>
#include "SceneObject.h"
#include "shaders/Shader.h"

namespace render_e {

// forward declaration
class SceneObject;

enum RenderMode {
    RENDER_MODE_FILL,
    RENDER_MODE_LINE,
    RENDER_MODE_POINT
};

class RenderBase {
public:
    void Display();

    void AddSceneObject(SceneObject *sceneObject);
    void DeleteSceneObject(SceneObject *sceneObject);
    
    void Init(void (*swapBuffersFunc)());
    void Reshape(int width, int height);
    
    
    void SetDoubleSpeedZOnlyRendering(bool enabled);
    bool GetDoubleSpeedZOnlyRendering();
    
    void SetRenderMode(RenderMode renderMode);
    void SetBackfaceCulling(bool enabled);

    void PrintDebug();

	SceneObject *Find(char *name);
    
    std::vector<SceneObject*> *GetSceneObjects() { return &sceneObjects; }
    std::vector<SceneObject*> *GetCameras() { return &cameras; }
    
    ///
    /// Reload all shaders from shader sources
    ///
    void ReloadAllShaders();
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
    inline void SetupLight();
    RenderBase();
    void RenderScene();
    static RenderBase *s_instance;
    std::vector<SceneObject*> sceneObjects;
    std::vector<SceneObject*> cameras;
    std::vector<SceneObject*> lights;
    std::map<std::string,Shader> shaders; 
    void (*swapBuffersFunc)();
    bool doubleSpeedZOnlyRendering;
    int width;
    int height;
};

}
#endif
