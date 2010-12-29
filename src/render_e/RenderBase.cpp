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

namespace render_e {

RenderBase *RenderBase::s_instance = NULL;

Shader *zOnlyShader = NULL;

RenderBase::RenderBase():swapBuffersFunc(NULL),doubleSpeedZOnlyRendering(true){
}

void RenderBase::Reshape(int width, int height){
    if (doubleSpeedZOnlyRendering){
        glDepthFunc(GL_LEQUAL);
        if (zOnlyShader == NULL){
            zOnlyShader = DefaultShaders::Instance()->GetZOnly();
        }
    } else {
        glDepthFunc(GL_LESS);
    }
}

void RenderBase::Display(){
    assert(swapBuffersFunc!=NULL);
    static SceneObject *lastCamera = NULL;
    
    for (std::vector<SceneObject *>::iterator iter = cameras.begin();iter!=cameras.end();iter++){
        if (lastCamera!=*iter){
            lastCamera = *iter;
            lastCamera->GetCamera()->Setup(); // only setup if changed
        }
        lastCamera->GetCamera()->Clear();
        // setup camera transform
#ifdef _DEBUG // make sure that the rendering takes place in MODELVIEW mode
        int matrixMode;
        glGetIntegerv(GL_MATRIX_MODE,&matrixMode);
        assert(matrixMode==GL_MODELVIEW);
#endif //_DEBUG
        Matrix44 cameraMatrix = lastCamera->GetTransform().GetLocalTransformInverse();
        RenderScene(cameraMatrix);
    }
    swapBuffersFunc();
}

void RenderBase::RenderScene(const Matrix44 &cameraMatrix){
    // Main idea here is to 
    if (doubleSpeedZOnlyRendering){
        //Disable color writes, and use flat shading for speed
        glShadeModel(GL_FLAT);
        glColorMask(0, 0, 0, 0);
        zOnlyShader->Bind();
        for (std::vector<SceneObject*>::iterator sIter = sceneObjects.begin();sIter!=sceneObjects.end();sIter++){
           MeshComponent *mesh = (*sIter)->GetMesh();
            Material *currentMaterial = (*sIter)->GetMaterial();
            if (mesh!=NULL){
                Matrix44 modelView = cameraMatrix*((*sIter)->GetTransform().GetLocalTransform());
                glLoadMatrixf(modelView.GetReference());
                mesh->Render();
            }
        }
        glShadeModel(GL_SMOOTH);
        glColorMask(1, 1, 1, 1);
    }
    
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
            Matrix44 modelView = cameraMatrix*((*sIter)->GetTransform().GetLocalTransform());
            glLoadMatrixf(modelView.GetReference());
            mesh->Render();
        }
    }
}

void RenderBase::AddSceneObject(SceneObject *sceneObject){
	assert(sceneObject != NULL);
    sceneObjects.push_back(sceneObject);
    if (sceneObject->GetCamera() != NULL){
        cameras.push_back(sceneObject);
    }
    
    if (sceneObject->GetLight() != NULL){
        lights.push_back(sceneObject);
    }
    
    using std::vector;
    vector<Transform*> *children = sceneObject->GetTransform().GetChildren();
    for (vector<Transform*>::iterator iter = children->begin();iter != children->end();iter++){
        std::cout<<"Children"<<std::endl;
        AddSceneObject((*iter)->GetSceneObject());
    }
}

void RenderBase::DeleteSceneObject(SceneObject *sceneObject){
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
}

void RenderBase::SetDoubleSpeedZOnlyRendering(bool enabled){
    this->doubleSpeedZOnlyRendering = enabled;
}

bool RenderBase::GetDoubleSpeedZOnlyRendering(){
    return doubleSpeedZOnlyRendering;
}
}
