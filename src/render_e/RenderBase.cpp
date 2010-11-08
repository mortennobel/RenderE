/*
 *  render_base.cpp
 *  RenderE
 *
 *  Created by morten on 10/28/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <algorithm>
#include <GL/glew.h>

#include "RenderBase.h"
#include "Camera.h"

namespace render_e {

RenderBase *RenderBase::s_instance = 0;

void RenderBase::Display(){
    static SceneObject *lastCamera = NULL;
    
    for (vector<SceneObject *>::iterator iter = cameras.begin();iter!=cameras.end();iter++){
        if (lastCamera!=*iter){
            lastCamera = *iter;
            lastCamera->GetCamera()->Setup(); // only setup if changed
        }
        lastCamera->GetCamera()->Clear();
        // setup camera transform
        glLoadIdentity();
 //       glMultMatrixf(lastCamera->GetTransform().);
        
        for (vector<SceneObject*>::iterator sIter = sceneObjects.begin();sIter!=sceneObjects.end();sIter++){
            (*sIter)->Render();
        }
    }
}

void RenderBase::AddSceneObject(SceneObject *sceneObject){
    sceneObjects.push_back(sceneObject);
    if (sceneObject->GetCamera() != NULL){
        cameras.push_back(sceneObject);
    }
}

void RenderBase::DeleteSceneObject(SceneObject *sceneObject){
    vector<SceneObject*>::iterator pos = find(sceneObjects.begin(), sceneObjects.end(), sceneObject);
    if (pos!=sceneObjects.end()){
        sceneObjects.erase(pos);
    }
    
    pos = find(cameras.begin(), cameras.end(), sceneObject);
    if (pos!=cameras.end()){
        cameras.erase(pos);
    }
}

}
