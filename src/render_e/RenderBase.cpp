/*
 *  render_base.cpp
 *  RenderE
 *
 *  Created by morten on 10/28/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <cstring>
#include <algorithm>
#include <GL/glew.h>

#include "RenderBase.h"
#include "Camera.h"
#include "shaders/DefaultShaders.h"
#include "OpenGLHelper.h"

#include <glm/gtc/type_ptr.hpp>

namespace render_e {

RenderBase *RenderBase::s_instance = NULL;

Shader *zOnlyShader = NULL;

RenderBase::RenderBase():swapBuffersFunc(NULL),doubleSpeedZOnlyRendering(true){
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

void RenderBase::Display(){
    assert(swapBuffersFunc!=NULL);
    
    
    for (std::vector<SceneObject *>::iterator iter = cameras.begin();iter!=cameras.end();iter++){
        SceneObject *sceneObject = *iter;
        Camera *camera = sceneObject->GetCamera();
        camera->Setup(width, height);
        camera->Clear();
        SetupLight();
        RenderScene();
        camera->TearDown();
    }
    swapBuffersFunc();
    OpenGLHelper::PrintErrors();
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

void RenderBase::PrintDebug(){
    using namespace std;
    cout << "Scene objects: "<<sceneObjects.size()<<endl;
    for (unsigned int i=0;i<sceneObjects.size();i++){
        cout <<sceneObjects[i]->GetName()<<endl;
        glm::vec3 position = sceneObjects[i]->GetTransform()->GetPosition();
        cout <<"Position "<<(int)position[0]<<" "<<(int)position[1]<<" "<<(int)position[2]<<" "<<endl;
        glm::quat q = sceneObjects[i]->GetTransform()->GetRotation();
        cout <<"Rotation "<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<endl;
        glm::vec3 scale = sceneObjects[i]->GetTransform()->GetScale();
        cout <<"Scale "<<(int)scale[0]<<" "<<(int)scale[1]<<" "<<(int)scale[2]<<" "<<endl;
        
    }
    
    cout << "Camera objects: "<<cameras.size()<<endl;
    for (unsigned int i=0;i<cameras.size();i++){
        cout <<cameras[i]->GetName()<<endl;
    }
    
    cout << "lights objects: "<<lights.size()<<endl;
    for (unsigned int i=0;i<lights.size();i++){
        cout <<lights[i]->GetName()<<endl;
    }
    
}
}
