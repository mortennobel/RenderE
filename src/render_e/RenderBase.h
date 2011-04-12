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
#include "shaders/ShaderDataSource.h"

namespace render_e {

// forward declaration
class SceneObject;

enum RenderMode {
    RENDER_MODE_FILL,
    RENDER_MODE_LINE,
    RENDER_MODE_POINT
};

///
/// The render base is the main class responsible updating and rendering
/// each component in the scene.
/// Note that the class is a singleton and a reference is received using the 
/// function Instance()
///
class RenderBase {
public:
    /// Should be invoked repeatedly from a render loop
    void Update(float timeSeconds = 0.1667f);

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
    /// Create a shader and store it in the shaders map.
    /// 
    Shader *CreateShader(std::string assetName, std::string shaderName, ShaderDataSource *shaderDataSource, ShaderLoadStatus &outLoadStatus);

    ///
    /// Change the shaderDataSource.
    /// This must be done before any shaders are loaded
    ///
    void SetShaderDataSource(ShaderDataSource *shaderDataSource);
    
    /// 
    /// Return the current instance of shader-data-source
    /// 
    ShaderDataSource *GetShaderDataSource(){ return shaderDataSource; }
    
    ///
    /// Reload all shaders from shader sources
    ///
    void ReloadAllShaders();
    
    ///
    /// Return the shader associated with a shaderName
    ///
    Shader *GetShader(std::string shaderName);
    
    ///
    /// Singleton pattern.
    /// return the render base instance
    ///
    static RenderBase* Instance() {
        if (!s_instance) {
            s_instance = new RenderBase();
        }
        return s_instance;
    }
private:
    inline void SetupLight();
    RenderBase();
    /// Render all objects in scene
    void RenderScene();
    /// Update all objects in scene
    void UpdateScene();
    static RenderBase *s_instance;
    std::vector<SceneObject*> sceneObjects;
    std::vector<SceneObject*> cameras;
    std::vector<SceneObject*> lights;
    std::map<std::string,Shader*> shaders; 
    void (*swapBuffersFunc)();
    bool doubleSpeedZOnlyRendering;
    int width;
    int height;
    ShaderDataSource *shaderDataSource;
};

}
#endif
