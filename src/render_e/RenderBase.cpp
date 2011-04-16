/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#include <cstring>
#include <sstream>
#include <algorithm>
#include <GL/glew.h>

#include "RenderBase.h"
#include "Camera.h"
#include "OpenGLHelper.h"
#include "shaders/ShaderFileDataSource.h"

#include <glm/gtc/type_ptr.hpp>

#include "Log.h"
#include "FrameTime.h"

namespace render_e {

RenderBase *RenderBase::s_instance = NULL;

Shader *zOnlyShader = NULL;

RenderBase::RenderBase():swapBuffersFunc(NULL),doubleSpeedZOnlyRendering(true){
    shaderDataSource = new ShaderFileDataSource();
}

Shader *RenderBase::CreateShader(std::string assetName, std::string shaderName, 
        ShaderDataSource *shaderDataSource, ShaderLoadStatus &outLoadStatus){
    Shader *s = Shader::CreateShader(assetName, shaderName, shaderDataSource, outLoadStatus);
    if (s != NULL){
        shaders[shaderName] = s;
    }
    return s;
}
    
Shader *RenderBase::GetShader(std::string shaderName){
    std::map<std::string,Shader*>::iterator iter = shaders.find(shaderName);
    if (iter != shaders.end()){
        return iter->second;
    }
    return NULL;
}

void RenderBase::SetShaderDataSource(ShaderDataSource *newShaderDataSource){
    assert(shaders.empty()); // cannot change shaderDataSource after the first shader is loaded
    delete shaderDataSource;
    shaderDataSource = newShaderDataSource;
}

void RenderBase::Reshape(int width, int height){
    this->width = width;
    this->height = height;
   /* if (doubleSpeedZOnlyRendering){
        glDepthFunc(GL_LEQUAL);
        if (zOnlyShader == NULL){
            zOnlyShader = DefaultShaders::Instance()->GetZOnly();
        }
    } else {
        glDepthFunc(GL_LESS);
    }*/
}

void RenderBase::SetupLight(){
    // Setup light
    // todo: this need not to run every frame
    int lightIndex=0;
    for (std::vector<SceneObject*>::iterator iter = lights.begin(); iter != lights.end();iter++){
        SceneObject *sceneObject = *iter;
        Light *light = sceneObject->GetLight(); 
        light->SetupLight(lightIndex);
        lightIndex++;
    }
}

void RenderBase::Update(float timeSeconds){
    assert(swapBuffersFunc!=NULL);
    
    FrameTime::updateTime(timeSeconds);
    UpdateScene();
    
    for (std::vector<SceneObject *>::iterator iter = cameras.begin();iter!=cameras.end();iter++){
        SceneObject *sceneObject = *iter;
        Camera *camera = sceneObject->GetCamera();
        camera->Setup(width, height);
        SetupLight();
        RenderScene();
        camera->TearDown();
    }
    swapBuffersFunc();
    OpenGLHelper::PrintErrors();
}


void RenderBase::UpdateScene(){
    // iterate all objects in scene and call their update function
    for (std::vector<SceneObject *>::iterator iter = sceneObjects.begin();iter!=sceneObjects.end();iter++){
        const std::vector<Component*> *comps = (*iter)->GetComponents();
        for (std::vector<Component*>::const_iterator componentIter = comps->begin();componentIter != comps->end(); componentIter++){
            (*componentIter)->Update();
        }
    }
}
    
void RenderBase::RenderScene(){
    // Main idea here is to <-- currently disabled
    /*if (doubleSpeedZOnlyRendering){
        //Disable color writes, and use flat shading for speed
        glShadeModel(GL_FLAT);
        glColorMask(0, 0, 0, 0);
        zOnlyShader->Bind();
        for (std::vector<SceneObject*>::iterator sIter = sceneObjects.begin();sIter!=sceneObjects.end();sIter++){
           MeshComponent *mesh = (*sIter)->GetMesh();
            Material *currentMaterial = (*sIter)->GetMaterial();
            if (mesh!=NULL){
                Matrix44 modelView = cameraMatrix*((*sIter)->GetTransform()->GetLocalTransform());
                glLoadMatrixf(modelView.GetReference());
                mesh->Render();
            }
        }
        glShadeModel(GL_SMOOTH);
        glColorMask(1, 1, 1, 1);
    }*/
    
    Material *lastMaterial = NULL;
    for (std::vector<SceneObject*>::iterator sIter = sceneObjects.begin();sIter!=sceneObjects.end();sIter++){
        MeshComponent *mesh = (*sIter)->GetMesh();
        Material *currentMaterial = (*sIter)->GetMaterial();
        if (currentMaterial != lastMaterial){
            if (currentMaterial != NULL){
                currentMaterial->Bind();
            }
            lastMaterial = currentMaterial;
        }
        if (mesh!=NULL){
            glPushMatrix();
            Transform *t = (*sIter)->GetTransform();
            glMultMatrixf(glm::value_ptr(t->GetLocalTransform()));
            mesh->Render();
            glPopMatrix();
        }
    }
}

void RenderBase::AddSceneObject(SceneObject *sceneObject){
	assert(sceneObject != NULL);
    
	sceneObject->SetRenderBase(this);
    sceneObjects.push_back(sceneObject);
    if (sceneObject->GetCamera() != NULL){
        cameras.push_back(sceneObject);
    }
    
    if (sceneObject->GetLight() != NULL){
        lights.push_back(sceneObject);
    }
    
    // add child components to the scene as well
    using std::vector;
    vector<Transform*> *children = sceneObject->GetTransform()->GetChildren();
    for (vector<Transform*>::iterator iter = children->begin();iter != children->end();iter++){
        AddSceneObject((*iter)->GetOwner());
    }
}

void RenderBase::DeleteSceneObject(SceneObject *sceneObject){
	sceneObject->SetRenderBase(NULL);
    std::vector<SceneObject*>::iterator pos = find(sceneObjects.begin(), sceneObjects.end(), sceneObject);
    if (pos!=sceneObjects.end()){
        sceneObjects.erase(pos);
    }
    
    pos = find(cameras.begin(), cameras.end(), sceneObject);
    if (pos!=cameras.end()){
        cameras.erase(pos);
    }
    
    pos = find(lights.begin(), lights.end(), sceneObject);
    if (pos!=cameras.end()){
        lights.erase(pos);
    }
}

SceneObject *RenderBase::Find(char *name){
    for (std::vector<SceneObject*>::iterator iter = sceneObjects.begin();iter != sceneObjects.end();iter++){
		if ((*iter)->GetName().compare(name)==0){
			return *iter;
		}
    }
	return NULL;
}

void RenderBase::SetRenderMode(RenderMode renderMode){
    GLenum renderModeValue;
    switch (renderMode){
        
        case RENDER_MODE_LINE:
            renderModeValue = GL_LINE;
            break;
        case RENDER_MODE_POINT:
            renderModeValue = GL_POINT;
            break;
        case RENDER_MODE_FILL:
        default:
            renderModeValue = GL_FILL;
            break;
    }
    glPolygonMode(GL_FRONT_AND_BACK, renderModeValue);
}

void RenderBase::Init(void (*swapBuffersFunc)()){
    this->swapBuffersFunc = swapBuffersFunc;
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0f);                         // 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);
}

void RenderBase::SetDoubleSpeedZOnlyRendering(bool enabled){
    this->doubleSpeedZOnlyRendering = enabled;
}

bool RenderBase::GetDoubleSpeedZOnlyRendering(){
    return doubleSpeedZOnlyRendering;
}

void RenderBase::ReloadAllShaders(){
    std::map<std::string,Shader*>::iterator shaderIter = shaders.begin();
    for (;shaderIter != shaders.end();shaderIter++){
        shaderIter->second->Reload();
    }
}

void RenderBase::PrintDebug(){
    using namespace std;
    stringstream ss;
    ss << "Scene objects: "<<sceneObjects.size()<<endl;
    for (unsigned int i=0;i<sceneObjects.size();i++){
        ss <<sceneObjects[i]->GetName()<<endl;
        glm::vec3 position = sceneObjects[i]->GetTransform()->GetPosition();
        ss <<"Position "<<(int)position[0]<<" "<<(int)position[1]<<" "<<(int)position[2]<<" "<<endl;
        glm::quat q = sceneObjects[i]->GetTransform()->GetRotation();
        ss <<"Rotation "<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<endl;
        glm::vec3 scale = sceneObjects[i]->GetTransform()->GetScale();
        ss <<"Scale "<<(int)scale[0]<<" "<<(int)scale[1]<<" "<<(int)scale[2]<<" "<<endl;
        
    }
    
    ss << "Camera objects: "<<cameras.size()<<endl;
    for (unsigned int i=0;i<cameras.size();i++){
        ss <<cameras[i]->GetName()<<endl;
    }
    
    ss << "lights objects: "<<lights.size()<<endl;
    for (unsigned int i=0;i<lights.size();i++){
        ss <<lights[i]->GetName()<<endl;
    }
    DEBUG(ss.str());
}
}
