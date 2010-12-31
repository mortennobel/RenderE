/* 
 * File:   FBXLoader.cpp
 * Author: morten
 * 
 * Created on December 10, 2010, 4:02 PM
 */

#include "FBXLoader.h"
#include <cassert>

#include <iostream>
#include "math/Vector3.h"
#include "math/Vector2.h"
#include "math/Mathf.h"
#include "MeshComponent.h"
#include "Mesh.h"


using namespace std;

#ifndef NO_FBX_LOADER

namespace render_e {
FBXLoader::FBXLoader() {
   manager = KFbxSdkManager::Create();
   int major, minor, revision;
   KFbxSdkManager::GetFileFormatVersion(major, minor, revision);
   cout<<"Created fbx sdk manager "<<major<<"."<<minor<<"."<<revision<<endl;
}

FBXLoader::FBXLoader(const FBXLoader& orig) {
}

FBXLoader::~FBXLoader() {
    manager->Destroy();
}

Vector3 toVector(const KFbxVector4 &v){
    return Vector3(v[0], v[1], v[2]);
}

Vector3 toVector(const fbxDouble3 &v){
    return Vector3(v[0], v[1], v[2]);
}


SceneObject* parseNode(KFbxNode *node, int level = 0) {
    KString s = node->GetName();
    KFbxNodeAttribute::EAttributeType attributeType;

    for (int i=0;i<level;i++){
        cout<<"   ";
    }
    SceneObject* sceneObject = NULL;
    MeshComponent* ga = NULL;
    
    if (node->GetNodeAttribute() == NULL){
        cout<<"No node attribute"<<endl;
    } else {
        attributeType = node->GetNodeAttribute()->GetAttributeType();
        switch (attributeType) {
            case KFbxNodeAttribute::eMARKER:
                cout<<"eMarker"<<endl;
                break;
            case KFbxNodeAttribute::eSKELETON:
                cout<<"eSkeleton"<<endl;
                break;
            case KFbxNodeAttribute::eMESH:
                {
                KFbxMesh *fbxMesh = node->GetMesh();
                KFbxVector4 *controlPoints = fbxMesh->GetControlPoints();
                int polygonCount = fbxMesh->GetPolygonCount();
                vector<Vector3> vertices;
                vector<Vector3> normals;
                vector<Vector2> texCords;
                vector<int> polycount;
                assert(fbxMesh->GetLayerCount(KFbxLayerElement::eNORMAL)==1); // assume only one normal layer
                KFbxLayer *normalLayer = fbxMesh->GetLayer(0, KFbxLayerElement::eNORMAL);
                KFbxLayerElementNormal *normalElement = normalLayer->GetNormals();
                KFbxLayerElementArrayTemplate<KFbxVector4> *normalArray = &(normalElement->GetDirectArray());
                
                int normalCount = normalArray->GetCount();
                vector<int> indices;
                
                assert(fbxMesh->GetControlPointsCount() <= USHRT_MAX);
                for (int i=0;i<fbxMesh->GetControlPointsCount();i++){
                    Vector3 v = toVector(controlPoints[i]);
                    cout<<v[0]<<" "<<v[1]<<" "<<v[2]<<endl;
                    vertices.push_back(v);
                    v = toVector(normalArray->GetAt(i));
                    cout<<"\t\t"<<v[0]<<" "<<v[1]<<" "<<v[2]<<endl;
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
                            cout<<first<<endl;
                            cout<<last<<endl;
                        }
                        int polygonIndex = fbxMesh->GetPolygonVertex(i,j);
                        indices.push_back(polygonIndex);
                        cout << polygonIndex<<endl;
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
                cout<<"Creating mesh: vertices "<<vertices.size()<<" normals "<<normals.size()<<" indices "<<indices.size()<<endl;
                mesh.SetVertices(vertices);
                mesh.SetNormals(normals);
                mesh.SetIndices(indices);
                sceneObject = new SceneObject();
                
                ga = new MeshComponent();
                ga->SetMesh(&mesh);
                sceneObject->AddCompnent(ga);
                
                // Set translate
                fbxDouble3 v3 = node->LclTranslation.Get();
                Vector3 translate = toVector(v3);
                sceneObject->GetTransform()->SetPosition(translate);
                
                // Set rotation
                v3 = node->LclRotation.Get();
                Vector3 rotation = toVector(v3)*Mathf::DEGREE_TO_RADIAN;
                sceneObject->GetTransform()->SetRotation(rotation);

                // Set scale
                v3 = node->LclScaling.Get();
                Vector3 scale = toVector(v3);
                sceneObject->GetTransform()->SetScale(scale);
                }
                break;
            case KFbxNodeAttribute::eCAMERA:
                cout<<"eCAMERA"<<endl;
                break;
            case KFbxNodeAttribute::eLIGHT:
                cout<<"eLIGHT"<<endl;
                break;
            case KFbxNodeAttribute::eBOUNDARY:
                cout<<"eBOUNDARY"<<endl;
                break;
            default:
                cout<<s<<endl;
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
    return sceneObject;
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
                cerr<<"ModelLoad import error "<<importer->GetLastErrorString()<<endl;
            }
        } else {
            cerr<<"ModelLoad init importer error "<<importer->GetLastErrorString()<<endl;
        }
    }
    importer->Destroy();
    scene->Destroy();
    return so;
}
}
#endif /* NO_FBX_LOADER */