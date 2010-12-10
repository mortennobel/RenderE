/* 
 * File:   FBXLoader.cpp
 * Author: morten
 * 
 * Created on December 10, 2010, 4:02 PM
 */

#include "FBXLoader.h"
#include <cassert>
#include "math/Vector3.h"
#include "math/Vector2.h"
#include "MeshComponent.h"
#include "Mesh.h"

#include <iostream>

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

Vector3 toVector(KFbxVector4 &v){
    return Vector3(v.GetAt(0), v.GetAt(1), v.GetAt(2));
}

MeshComponent* parseNode(KFbxNode *node, int level = 0) {
    KString s = node->GetName();
    KFbxNodeAttribute::EAttributeType attributeType;

    for (int i=0;i<level;i++){
        cout<<"   ";
    }

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
                /*cout<<s<<" size "<<normalCount<<endl;
                for (int i=0;i<polygonCount;i++){
                    int polygonSize = mesh->GetPolygonSize(i);
                    polycount.push_back(polygonSize);
                    for (int j=0;j<polygonSize;j++){
                        int polygonIndex = mesh->GetPolygonVertex(i,j);
                        KFbxVector4 vectorSrc = controlPoints[polygonIndex];
                        Vector3 vectorDst = toVector(vectorSrc);
                        vertices.push_back(vectorDst);
                        texCords.push_back(Vector2(0,0)); 
                        KFbxVector4 normalSrc = normalArray->GetAt(polygonIndex);
                        Vector3 normalDst = toVector(normalSrc);
                        normals.push_back(normalDst);
                    }
                }*/
                
                Mesh mesh;
                
                ga = new MeshComponent();
                ga->SetMesh(&mesh);
                // set translate
                /*KFbxVector4 v4;
                node->GetDefaultT(v4);
                Vector3f translate = toVector(v4);
                ga->GetTransform()->SetTranslate(&translate);
                node->GetDefaultR(v4);
                Vector3f rotation = toVector(v4);
                if (rotation.LengthSquared()!=0){
                    ga->GetTransform()->SetRotateX(rotation.x);
                    ga->GetTransform()->SetRotateY(rotation.y);
                    ga->GetTransform()->SetRotateZ(rotation.z);
                }
                node->GetDefaultS(v4);
                Vector3f scale = toVector(v4);
                if (rotation.LengthSquared()!=0){
                    ga->GetTransform()->SetScaleX(scale.x);
                    ga->GetTransform()->SetScaleY(scale.y);
                    ga->GetTransform()->SetScaleZ(scale.z);
                }*/
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
    /*
    if (node->GetChildCount()>0){
        GameObjectParent *parent = new GameObjectParent();
        if (ga != NULL) {
            parent->AddGameObject(ga);
        }
        for (int i=0;i<node->GetChildCount();i++){
            GameObject *res = parseNode(node->GetChild(i),level+1);
            if (res!=NULL){
                parent->AddGameObject(res);
            }
        }

        ga = parent;
    }
    */
    return ga;
}

MeshComponent *FBXLoader::Load(const char *filename){
    MeshComponent *ga = NULL;
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
                ga = parseNode(node);
            } else {
                cerr<<"ModelLoad import error "<<importer->GetLastErrorString()<<endl;
            }
        } else {
            cerr<<"ModelLoad init importer error "<<importer->GetLastErrorString()<<endl;
        }
    }
    importer->Destroy();
    scene->Destroy();
    return ga;
}
}
#endif /* NO_FBX_LOADER */