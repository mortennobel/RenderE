/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#include "FBXLoader.h"
#include <cassert>

#include <iostream>
#include <sstream>
#include <glm/glm.hpp>
#include "render_e/Mathf.h"
#include "render_e/MeshComponent.h"
#include "render_e/SceneObject.h"
#include "render_e/Mesh.h"
#include "render_e/Log.h"

using namespace std;

#ifndef NO_FBX_LOADER

namespace render_e {
FBXLoader::FBXLoader() {
   manager = KFbxSdkManager::Create();
   int major, minor, revision;
   KFbxSdkManager::GetFileFormatVersion(major, minor, revision);
   stringstream ss;
   ss<<"Created fbx sdk manager "<<major<<"."<<minor<<"."<<revision;
   INFO(ss.str());
}

FBXLoader::FBXLoader(const FBXLoader& orig) {
}

FBXLoader::~FBXLoader() {
    manager->Destroy();
}

glm::vec3 toVector(const KFbxVector4 &v){
    return glm::vec3(v[0], v[1], v[2]);
}

glm::vec3 toVector(const fbxDouble3 &v){
    return glm::vec3(v[0], v[1], v[2]);
}

SceneObject* parseNode(KFbxNode *node, int level = 0) {
    KString s = node->GetName();
    KFbxNodeAttribute::EAttributeType attributeType;
    stringstream ss;
    for (int i=0;i<level;i++){
        ss<<"   ";
    }
    SceneObject* sceneObject = NULL;
    MeshComponent* ga = NULL;
    
    if (node->GetNodeAttribute() == NULL){
        ss<<"No node attribute"<<endl;
    } else {
        attributeType = node->GetNodeAttribute()->GetAttributeType();
        switch (attributeType) {
            case KFbxNodeAttribute::eMARKER:
                ss<<"eMarker"<<endl;
                break;
            case KFbxNodeAttribute::eSKELETON:
                ss<<"eSkeleton"<<endl;
                break;
            case KFbxNodeAttribute::eMESH:
                {
                KFbxMesh *fbxMesh = node->GetMesh();
                KFbxVector4 *controlPoints = fbxMesh->GetControlPoints();
                int polygonCount = fbxMesh->GetPolygonCount();
                vector<glm::vec3> vertices;
                vector<glm::vec3> normals;
                vector<glm::vec2> texCords;
                vector<int> polycount;
                assert(fbxMesh->GetLayerCount(KFbxLayerElement::eNORMAL)==1); // assume only one normal layer
                KFbxLayer *normalLayer = fbxMesh->GetLayer(0, KFbxLayerElement::eNORMAL);
                KFbxLayerElementNormal *normalElement = normalLayer->GetNormals();
                KFbxLayerElementArrayTemplate<KFbxVector4> *normalArray = &(normalElement->GetDirectArray());
                
                int normalCount = normalArray->GetCount();
                vector<int> indices;
                
                assert(fbxMesh->GetControlPointsCount() <= USHRT_MAX);
                for (int i=0;i<fbxMesh->GetControlPointsCount();i++){
                    glm::vec3 v = toVector(controlPoints[i]);
                    vertices.push_back(v);
                    v = toVector(normalArray->GetAt(i));
                    normals.push_back(v);
                }
                
                
                for (int i=0;i<polygonCount;i++){
                    int polygonSize = fbxMesh->GetPolygonSize(i);
                    polycount.push_back(polygonSize);
                    for (int j=0;j<polygonSize;j++){
                        if (j>2){
                            // if polygon size > 2 then add first and last index
                            // this triangulates the mesh
                            int first = fbxMesh->GetPolygonVertex(i,0);
                            int last = fbxMesh->GetPolygonVertex(i,j-1);
                            indices.push_back(first);
                            indices.push_back(last);
                        }
                        int polygonIndex = fbxMesh->GetPolygonVertex(i,j);
                        indices.push_back(polygonIndex);
                        /*KFbxVector4 vectorSrc = controlPoints[polygonIndex];
                        Vector3 vectorDst = toVector(vectorSrc);
                        vertices.push_back(vectorDst);
                        texCords.push_back(Vector2(0,0)); 
                        KFbxVector4 normalSrc = normalArray->GetAt(polygonIndex);
                        Vector3 normalDst = toVector(normalSrc);
                        normals.push_back(normalDst);*/
                    }
                }
                
                Mesh mesh;
                ss<<"Creating mesh: vertices "<<vertices.size()<<" normals "<<normals.size()<<" indices "<<indices.size()<<endl;
                mesh.SetVertices(vertices);
                mesh.SetNormals(normals);
                mesh.SetIndices(indices);
                sceneObject = new SceneObject();
                
                ga = new MeshComponent();
                ga->SetMesh(&mesh);
                sceneObject->AddCompnent(ga);
                
                // Set translate
                fbxDouble3 v3 = node->LclTranslation.Get();
                glm::vec3 translate = toVector(v3);
                sceneObject->GetTransform()->SetPosition(translate);
                
                // Set rotation
                v3 = node->LclRotation.Get();
                glm::vec3 rotation = toVector(v3)*Mathf::DEGREE_TO_RADIAN;
                sceneObject->GetTransform()->SetRotation(rotation);

                // Set scale
                v3 = node->LclScaling.Get();
                glm::vec3 scale = toVector(v3);
                sceneObject->GetTransform()->SetScale(scale);
                }
                break;
            case KFbxNodeAttribute::eCAMERA:
                ss<<"eCAMERA"<<endl;
                break;
            case KFbxNodeAttribute::eLIGHT:
                ss<<"eLIGHT"<<endl;
                break;
            case KFbxNodeAttribute::eBOUNDARY:
                ss<<"eBOUNDARY"<<endl;
                break;
            default:
                ss<<s<<endl;
        }
    }
    
    if (node->GetChildCount()>0){
        for (int i=0;i<node->GetChildCount();i++){
            SceneObject *res = parseNode(node->GetChild(i),level+1);
            if (res!=NULL){
                if (sceneObject == NULL){
                    sceneObject = new SceneObject();
                }
                sceneObject->AddChild(res);
            }
        }
    }
    DEBUG(ss.str());
    return sceneObject;
}

MeshComponent *getMeshComponent(SceneObject *sceneObject){
	MeshComponent *mesh = sceneObject->GetMesh(); 
	if (mesh!= NULL){
		return mesh;
	}

	// search in children
	const vector<Transform*> *children = sceneObject->GetTransform()->GetChildren();
	for (vector<Transform*>::const_iterator iter = children->begin();iter != children->end();iter++){
		Transform *childTransform = *iter;
		SceneObject *child = childTransform->GetOwner();
		if (child != NULL){
			mesh = getMeshComponent(child);
			if (mesh!=NULL){
				return mesh;
			}
		}
	}

	return NULL;
}

MeshComponent *FBXLoader::LoadMeshComponent(const char *filename){
	SceneObject *sceneObject = Load(filename);
	// Here there is a memory leak!!!
	return getMeshComponent(sceneObject);
}

SceneObject *FBXLoader::Load(const char *filename){
    SceneObject *so = NULL;
    KFbxScene *scene = KFbxScene::Create(manager, "");
    KFbxImporter *importer = KFbxImporter::Create(manager, "");
    int fileFormat = -1;
    const bool fileFormatFound =
            manager->GetIOPluginRegistry()->DetectReaderFileFormat(filename, fileFormat);
    if (fileFormatFound) {
        bool initSuccess = importer->Initialize(filename, fileFormat);
        if (initSuccess) {
           
            bool importSuccess = importer->Import(scene);   
            if (importSuccess) {
                KFbxNode *node = scene->GetRootNode();
                so = parseNode(node);
            } else {
                stringstream ss;
                ss<<"ModelLoad import error "<<importer->GetLastErrorString();
                ERROR(ss.str());
            }
        } else {
            stringstream ss;
            ss<<"ModelLoad init importer error "<<importer->GetLastErrorString();
            ERROR(ss.str());
        }
    }
    importer->Destroy();
    scene->Destroy();
    return so;
}
}
#endif /* NO_FBX_LOADER */